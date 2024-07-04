//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>
//#include <OgreFrameListener.h>
//#include <OgreOverlaySystem.h>
//#include <OgreOverlayManager.h>
//#include <OgreOverlay.h>
//#include <OgreOverlayContainer.h>
//#include <iostream>
//
//class Practice15 : public OgreBites::ApplicationContext, public OgreBites::InputListener {
//public:
//    Practice15() : OgreBites::ApplicationContext("Practice14"), hpForeground(nullptr) {}
//
//    void setup() override {
//        OgreBites::ApplicationContext::setup();
//        addInputListener(this);
//
//        Ogre::Root* root = getRoot();
//        Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//        // RTSS(실시간 셰이더 시스템)에 장면 등록
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(scnMgr);
//
//        // 카메라 생성
//        Ogre::Camera* cam = scnMgr->createCamera("myCam");
//        cam->setNearClipDistance(5);
//        cam->setAutoAspectRatio(true);
//
//        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        camNode->attachObject(cam);
//        camNode->setPosition(0, 50, 200);
//        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
//
//        getRenderWindow()->addViewport(cam);
//
//        // 조명 생성
//        Ogre::Light* light = scnMgr->createLight("MainLight");
//        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode->setPosition(0, 150, 250);
//        lightNode->attachObject(light);
//
//        // 바닥면 생성
//        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
//        Ogre::MeshManager::getSingleton().createPlane(
//            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
//            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
//        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
//        ent->setMaterialName("Examples/BeachStones");
//
//        // 입자 시스템 생성
//        Ogre::ParticleSystem* partSystem = scnMgr->createParticleSystem("Smoke", "Examples/Smoke");
//        Ogre::SceneNode* partNode = scnMgr->getRootSceneNode()->createChildSceneNode("ParticleNode");
//        partNode->attachObject(partSystem);
//        partNode->setPosition(0, 0, 0);
//
//        // 오버레이 관리자 생성 및 설정
//        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
//        Ogre::Overlay* overlay = overlayManager.create("OverlayName");
//
//        // HP 바 컨테이너 생성
//        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
//            overlayManager.createOverlayElement("Panel", "PanelName"));
//        panel->setMetricsMode(Ogre::GMM_PIXELS);
//        panel->setPosition(10, 10);
//        panel->setDimensions(200, 30);
//        panel->setMaterialName("BaseWhite");
//
//        // HP 바 배경
//        Ogre::OverlayElement* hpBackground = overlayManager.createOverlayElement("Panel", "HPBackground");
//        hpBackground->setMetricsMode(Ogre::GMM_PIXELS);
//        hpBackground->setPosition(0, 0);
//        hpBackground->setDimensions(200, 30);
//        hpBackground->setMaterialName("BaseWhite");
//
//        // HP 바 전경
//        hpForeground = overlayManager.createOverlayElement("Panel", "HPForeground");
//        hpForeground->setMetricsMode(Ogre::GMM_PIXELS);
//        hpForeground->setPosition(0, 0);
//        hpForeground->setDimensions(200, 30);
//        hpForeground->setMaterialName("HP/Green");
//
//        panel->addChild(hpBackground);
//        panel->addChild(hpForeground);
//        overlay->add2D(panel);
//        overlay->setZOrder(500);  // 오버레이를 항상 앞쪽에 표시
//        overlay->show();
//    }
//
//    void updateHPBar(float percentage) {
//        if (hpForeground) {
//            hpForeground->setDimensions(200 * percentage, 30);
//        }
//    }
//
//private:
//    Ogre::OverlayElement* hpForeground;
//};
//
//int main(int argc, char** argv) {
//    try {
//        Practice15 app;
//        app.initApp();
//
//        // 예제: HP 바를 50%로 설정
//        app.updateHPBar(0.5);
//
//        app.getRoot()->startRendering();
//        app.closeApp();
//    }
//    catch (Ogre::Exception& e) {
//        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
//    }
//    return 0;
//}

//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreOverlaySystem.h>
//#include <OgreOverlayManager.h>
//#include <OgreOverlay.h>
//#include <OgreOverlayContainer.h>
//#include <OgreTextAreaOverlayElement.h>
//#include <OgreTrays.h>  // TrayManager를 사용하기 위해 추가
//#include <iostream>
//
//class TextOverlayApp : public OgreBites::ApplicationContext, public OgreBites::InputListener {
//public:
//    TextOverlayApp() : OgreBites::ApplicationContext("TextOverlayApp"), trayMgr(nullptr) {}
//
//    void setup() override {
//        OgreBites::ApplicationContext::setup();
//        addInputListener(this);  // 이제 TextOverlayApp은 InputListener를 구현하므로 이 줄이 정상 작동해야 함
//
//        Ogre::Root* root = getRoot();
//        Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//        // RTSS(실시간 셰이더 시스템)에 장면 등록
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(scnMgr);
//
//        Ogre::RTShader::RenderState* pMainRenderState =
//            shadergen->createOrRetrieveRenderState(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME).first;
//        pMainRenderState->resetToBuiltinSubRenderStates();
//
//        // 카메라 생성
//        Ogre::Camera* cam = scnMgr->createCamera("myCam");
//        cam->setNearClipDistance(5);
//        cam->setAutoAspectRatio(true);
//
//        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        camNode->attachObject(cam);
//         camNode->setPosition(0, 50, 200);
//        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
//
//        getRenderWindow()->addViewport(cam);
//
//        //조명
//        Ogre::Light* light = scnMgr->createLight("MainLight");
//        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//        lightNode->setPosition(0, 150, 250);
//        lightNode->attachObject(light);
//
//        // 바닥면 생성
//        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
//        Ogre::MeshManager::getSingleton().createPlane(
//            "plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
//            1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//        Ogre::Entity* ent = scnMgr->createEntity("LightPlaneEntity", "plane");
//        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
//        ent->setMaterialName("Examples/BeachStones");
//
//        // 오버레이 관리자 생성
//        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
//        Ogre::Overlay* overlay = overlayManager.create("OverlayName");
//
//        // 텍스트 오버레이 생성
//        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
//            overlayManager.createOverlayElement("Panel", "PanelName"));
//        panel->setPosition(0.5, 0.5);
//        panel->setDimensions(0.1, 0.1);
//        panel->setMaterialName("BaseWhiteNoLighting");  // 투명 배경을 위해 사용
//
//        // 패널에 배경색 설정
//        panel->setColour(Ogre::ColourValue(0.5, 0.5, 0.5, 0.7)); // RGBA 색상 설정 (0.5, 0.5, 0.5)은 회색, 0.7은 투명도
//
//        // 텍스트 오버레이 요소 생성
//        Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
//            overlayManager.createOverlayElement("TextArea", "TextView"));
//        textArea->setMetricsMode(Ogre::GMM_PIXELS);
//        textArea->setPosition(10, 10);
//        textArea->setDimensions(380, 80);
//        textArea->setCharHeight(26);  // 텍스트 크기 설정
//        textArea->setFontName("SdkTrays/Value");
//        textArea->setCaption("Hello, Ogre!");
//        textArea->setColourBottom(Ogre::ColourValue::Black);  // 텍스트 색상 설정
//
//        // 패널에 텍스트 요소 추가
//        panel->addChild(textArea);
//
//        // 오버레이에 패널 추가 및 표시
//        overlay->add2D(panel);
//        overlay->setZOrder(500);  // 오버레이를 항상 앞쪽에 표시
//        overlay->show();
//
//        // TrayManager 생성
//        trayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow(), nullptr); // TrayListener를 nullptr로 전달
//
//        // 다양한 UI 요소 생성
//        titleLabel = trayMgr->createLabel(OgreBites::TL_TOPLEFT, "SampleTitle", "Sample Title");
//        descBox = trayMgr->createTextBox(OgreBites::TL_TOPLEFT, "SampleInfo", "Sample Info", 300, 208);
//        categoryMenu = trayMgr->createThickSelectMenu(OgreBites::TL_TOPLEFT, "CategoryMenu", "Select Category", 300, 10);
//        sampleMenu = trayMgr->createThickSelectMenu(OgreBites::TL_TOPLEFT, "SampleMenu", "Select Sample", 300, 10);
//        sampleSlider = trayMgr->createThickSlider(OgreBites::TL_TOPLEFT, "SampleSlider", "Slide Samples", 300, 80, 0, 0, 0);
//
//        // 트레이 매니저 활성화
//        trayMgr->showAll();
//    }
//
//
//private:
//    OgreBites::TrayManager* trayMgr;
//    OgreBites::Label* titleLabel;
//    OgreBites::TextBox* descBox;
//    OgreBites::SelectMenu* categoryMenu;
//    OgreBites::SelectMenu* sampleMenu;
//    OgreBites::Slider* sampleSlider;
//};
//
//int main(int argc, char** argv) {
//    try {
//        TextOverlayApp app;
//        app.initApp();
//        app.getRoot()->startRendering();
//        app.closeApp();
//    }
//    catch (Ogre::Exception& e) {
//        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
//    }
//    return 0;
//}

//#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>
//#include <OgreTrays.h>
//#include <OgreOverlaySystem.h>
//#include <OgreOverlayManager.h>
//#include <OgreOverlayContainer.h>
//#include <iostream>
//
//class Practice15 : public OgreBites::ApplicationContext, public OgreBites::InputListener
//{
//public:
//    Practice15() : OgreBites::ApplicationContext("Practice15"), mTrayMgr(nullptr) {}
//
//    void setup() override
//    {
//        // 기본 설정 호출
//        OgreBites::ApplicationContext::setup();
//
//        // 이미 생성된 루트 포인터 가져오기
//        Ogre::Root* root = getRoot();
//        Ogre::RenderWindow* window = getRenderWindow();
//
//        // 리소스 설정 파일 로드
//        if (!Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("General"))
//        {
//            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media", "FileSystem", "General");
//            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//        }
//
//        // SceneManager 생성
//        Ogre::SceneManager* sceneMgr = root->createSceneManager();
//
//        // OverlaySystem 생성 (이미 생성된 경우 무시)
//        if (!Ogre::OverlaySystem::getSingletonPtr())
//            mOverlaySystem = new Ogre::OverlaySystem();
//        else
//            mOverlaySystem = Ogre::OverlaySystem::getSingletonPtr();
//
//        // SceneManager에 OverlaySystem 추가
//        sceneMgr->addRenderQueueListener(mOverlaySystem);
//
//        // RTSS와 장면 등록
//        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//        shadergen->addSceneManager(sceneMgr);
//
//        // 카메라 생성
//        Ogre::Camera* cam = sceneMgr->createCamera("myCam");
//        cam->setAutoAspectRatio(true);
//        cam->setNearClipDistance(5);
//
//        // 뷰포트 생성
//        Ogre::Viewport* vp = window->addViewport(cam);
//        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
//
//        // Overlay 생성
//        createOverlay();
//
//        // 기본 TrayManager 생성
//        mTrayMgr = new OgreBites::TrayManager("InterfaceName", window);
//        addInputListener(mTrayMgr);
//
//        // 버튼 생성
//        OgreBites::Button* button = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Click Me!");
//        mTrayMgr->showAll();
//    }
//
//    void createOverlay()
//    {
//        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
//
//        // 이미 정의된 OverlayElement 가져오기
//        Ogre::OverlayElement* panel = overlayManager.getOverlayElement("SdkTrays/Tray");
//
//        // 패널 설정
//        panel->setMetricsMode(Ogre::GMM_PIXELS);
//        panel->setPosition(10, 10);
//        panel->setDimensions(300, 120);
//
//        // Overlay 생성 및 추가
//        Ogre::Overlay* overlay = overlayManager.create("myOverlay");
//        overlay->add2D(static_cast<Ogre::OverlayContainer*>(panel));
//        overlay->show();
//    }
//
//private:
//    Ogre::OverlaySystem* mOverlaySystem;
//    OgreBites::TrayManager* mTrayMgr;
//};
//
//int main(int argc, char** argv)
//{
//    try {
//        Practice15 app;
//        app.initApp();
//        app.getRoot()->startRendering();
//        app.closeApp();
//    }
//    catch (Ogre::Exception& e) {
//        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
//    }
//    return 0;
//}

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <iostream>

class Practice15 : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{
public:
    Practice15() : OgreBites::ApplicationContext("Practice15"), mTrayMgr(nullptr), mHpBar(nullptr), mScoreLabel(nullptr), mScore(0) {}

    void setup() override
    {
        // 기본 설정 호출
        OgreBites::ApplicationContext::setup();

        // 이미 생성된 루트 포인터 가져오기
        Ogre::Root* root = getRoot();
        Ogre::RenderWindow* window = getRenderWindow();

        //// 리소스 설정 파일 로드
        //if (!Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("General"))
        //{
        //    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media", "FileSystem", "General");
        //    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
        //}

        // SceneManager 생성
        Ogre::SceneManager* sceneMgr = root->createSceneManager();

        // OverlaySystem 생성 (이미 생성된 경우 무시)
        if (!Ogre::OverlaySystem::getSingletonPtr())
            mOverlaySystem = new Ogre::OverlaySystem();
        else
            mOverlaySystem = Ogre::OverlaySystem::getSingletonPtr();

        // SceneManager에 OverlaySystem 추가
        sceneMgr->addRenderQueueListener(mOverlaySystem);

        // RTSS와 장면 등록
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(sceneMgr);

        // 카메라 생성
        Ogre::Camera* cam = sceneMgr->createCamera("myCam");
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

        // HP 바 슬라이더 생성
        mHpBar = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT, "HPBar", "HP", 300, 100, 0, 100, 100);
        mHpBar->setValue(100); // 초기 HP를 100으로 설정

        // 스코어 라벨 생성
        mScoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "ScoreLabel", "Score: 0", 200);

        mTrayMgr->showAll();
    }

    void createOverlay()
    {
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

        // 이미 정의된 OverlayElement 가져오기
        Ogre::OverlayElement* panel = overlayManager.getOverlayElement("SdkTrays/Tray");

        // 패널 설정
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(10, 10);
        panel->setDimensions(300, 120);

        // Overlay 생성 및 추가
        Ogre::Overlay* overlay = overlayManager.create("myOverlay");
        overlay->add2D(static_cast<Ogre::OverlayContainer*>(panel));
        overlay->show();
    }

    void sliderMoved(OgreBites::Slider* slider) override
    {
        if (slider->getName() == "HPBar")
        {
            int hp = slider->getValue();
            std::cout << "HP: " << hp << std::endl;
        }
    }

    void buttonHit(OgreBites::Button* button) override
    {
        if (button->getName() == "MyButton")
        {
            mScore += 10;
            mScoreLabel->setCaption("Score: " + std::to_string(mScore));
            std::cout << "Score: " << mScore << std::endl;
        }
    }

private:
    Ogre::OverlaySystem* mOverlaySystem;
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::Slider* mHpBar;
    OgreBites::Label* mScoreLabel;
    int mScore;
};

int main(int argc, char** argv)
{
    try {
        Practice15 app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (Ogre::Exception& e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}

