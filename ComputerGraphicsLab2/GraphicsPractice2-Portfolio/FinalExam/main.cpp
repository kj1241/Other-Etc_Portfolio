#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>
#include <iostream>
#include <chrono>

enum class SceneType
{
    Start,
    Main,
    End
};

class FinalExamFrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    SceneType* mCurrentScene;
    std::chrono::steady_clock::time_point mSceneStartTime;

public:
    FinalExamFrameListener(SceneType* currentScene)
        : mCurrentScene(currentScene), mSceneStartTime(std::chrono::steady_clock::now())
    {
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        return true;
    }

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override
    {
        return true;
    }

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override
    {
        return true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - mSceneStartTime).count();

        if (elapsed >= 30)
        {
            switch (*mCurrentScene)
            {
            case SceneType::Start:
                *mCurrentScene = SceneType::Main;
                break;
            case SceneType::Main:
                *mCurrentScene = SceneType::End;
                break;
            case SceneType::End:
                *mCurrentScene = SceneType::Start;
                break;
            }
            mSceneStartTime = now;
        }

        return true;
    }
};

class FinalExam : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{
public:
    FinalExam() : OgreBites::ApplicationContext("FinalExam"), mTrayMgr(nullptr), mCurrentScene(SceneType::Start), mOverlaySystem(nullptr), mSceneMgr(nullptr) {}

    void setup() override
    {
        // 기본 설정 호출
        OgreBites::ApplicationContext::setup();

        // 이미 생성된 루트 포인터 가져오기
        Ogre::Root* root = getRoot();
        Ogre::RenderWindow* window = getRenderWindow();

        // 리소스 설정 파일 로드
        if (!Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("General"))
        {
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media", "FileSystem", "General");
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
        }

        // SceneManager 생성
        mSceneMgr = root->createSceneManager();

        // OverlaySystem 생성 (이미 생성된 경우 무시)
        if (!Ogre::OverlaySystem::getSingletonPtr())
            mOverlaySystem = new Ogre::OverlaySystem();
        else
            mOverlaySystem = Ogre::OverlaySystem::getSingletonPtr();

        // SceneManager에 OverlaySystem 추가
        mSceneMgr->addRenderQueueListener(mOverlaySystem);

        // RTSS와 장면 등록
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(mSceneMgr);

        // 카메라 생성
        cam = mSceneMgr->createCamera("myCam");
        cam->setAutoAspectRatio(true);
        cam->setNearClipDistance(5);

        // 뷰포트 생성
        Ogre::Viewport* vp = window->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

        // Overlay 생성
        createOverlay();

        // 기본 TrayManager 생성
        mTrayMgr = new OgreBites::TrayManager("InterfaceName", window, this);
        addInputListener(mTrayMgr);

        // FrameListener 생성 및 추가
        FinalExamFrameListener* frameListener = new FinalExamFrameListener(&mCurrentScene);
        root->addFrameListener(frameListener);
        addInputListener(frameListener);

        // 초기 씬 설정
        changeScene();
    }

    void buttonHit(OgreBites::Button* button) override
    {
        if (button->getName() == "MyButton")
        {
            mCurrentScene = SceneType::Main;
            changeScene();
        }
    }

    void changeScene()
    {
        mSceneMgr->clearScene();
        mTrayMgr->destroyAllWidgets();
        mOverlay->hide();

        switch (mCurrentScene)
        {
        case SceneType::Start:
            mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Start");
            mTrayMgr->showAll();
            break;
        case SceneType::Main:
            setupMainScene();
            break;
        case SceneType::End:
        {
            Ogre::OverlayElement* textArea = Ogre::OverlayManager::getSingleton().getOverlayElement("TextArea");
            textArea->setCaption("Score: 0");
            mOverlay->show();
        }
        break;
        }
    }

    void createOverlay()
    {
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

        // 컨테이너 생성
        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
            overlayManager.createOverlayElement("Panel", "ContainerPanel"));
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(10, 10);
        panel->setDimensions(300, 120);

        // 텍스트 영역 추가
        Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
            overlayManager.createOverlayElement("TextArea", "TextArea"));
        textArea->setMetricsMode(Ogre::GMM_PIXELS);
        textArea->setPosition(0, 0); // 패널 내의 상대적인 위치
        textArea->setDimensions(300, 120);
        textArea->setCaption("Score: 0");
        textArea->setCharHeight(26);
        textArea->setFontName("SdkTrays/Caption");

        // 텍스트 영역을 패널에 추가
        panel->addChild(textArea);

        // Overlay 생성 및 패널 추가
        mOverlay = overlayManager.create("myOverlay");
        mOverlay->add2D(panel);
        mOverlay->hide();
    }

    void setupMainScene()
    {
        Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();


        camNode->setPosition(0, 59, 322);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
        camNode->attachObject(cam);

        // 조명 추가
        Ogre::Light* light = mSceneMgr->createLight("Light");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        //light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

        Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(20, 80, 50);
        lightNode->attachObject(light);

        Ogre::Entity* sphereEntity = mSceneMgr->createEntity("MySphere", Ogre::SceneManager::PT_SPHERE);
        sphereEntity->setMaterialName("Examples/TextureEffect2");
        Ogre::SceneNode* sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
        sphereNode->setPosition(0, 0, 0);
        sphereNode->setScale(0.1f, 0.1f, 0.1f);
        sphereNode->attachObject(sphereEntity);
    }

private:
    Ogre::Camera* cam;


    Ogre::OverlaySystem* mOverlaySystem;
    OgreBites::TrayManager* mTrayMgr;
    SceneType mCurrentScene;
    Ogre::Overlay* mOverlay;
    Ogre::SceneManager* mSceneMgr;
};

int main(int argc, char** argv)
{
    FinalExam app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
