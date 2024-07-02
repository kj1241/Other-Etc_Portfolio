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
        // ���� �⺻ ���� ȣ��
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        // �̹� ������ ��Ʈ ������ ��������
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        // RTSS�� ��� ���
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // �� ������ ������ ��ü���� ������� ���� �� �ֽ��ϴ�
        scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
        scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

        // ī�޶� ����
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5); // �� ���ÿ� Ưȭ�� ��
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        camNode->setPosition(0, 0, 140);
        camNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TS_PARENT);

        // �� â�� �������ϵ��� ����
        getRenderWindow()->addViewport(cam);

        // ���������� �������� ����� ����
        createScene(scnMgr);
    }

    virtual void createScene(Ogre::SceneManager* scnMgr) = 0;
};
