#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>

class ExampleApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    ExampleApplication() : OgreBites::ApplicationContext("OgreTutorialApp") {}

    void setup() override
    {
        // 먼저 기본 설정 호출
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        // 이미 생성된 루트 포인터 가져오기
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        // RTSS에 장면 등록
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // 이 설정이 없으면 객체들이 평면으로 보일 수 있습니다
        scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
        scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

        // 카메라 생성
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5); // 이 샘플에 특화된 값
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        camNode->setPosition(0, 0, 140);
        camNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TS_PARENT);

        // 주 창에 렌더링하도록 설정
        getRenderWindow()->addViewport(cam);

        // 마지막으로 렌더링할 장면을 생성
        createScene(scnMgr);
    }

    virtual void createScene(Ogre::SceneManager* scnMgr) = 0;
};
