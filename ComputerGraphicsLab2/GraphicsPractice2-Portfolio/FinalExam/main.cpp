#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include <OgreMaterialManager.h>
#include <OgreRTShaderSystem.h>
#include <OgreCompositorManager.h>
#include <OgreParticleSystem.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

enum class SceneType
{
    Start,
    Main,
    End
};

class FianlExamFrameListener : public Ogre::FrameListener, public OgreBites::InputListener
{
private:
    enum MonsterState
    {
        none=0,
        alive,
        particle,
        daeth
    };
    //몬스터
    struct AIMonster
    {
        MonsterState monsterState=none;
        Ogre::Entity* mMonsters;
        Ogre::SceneNode* mMonstersNode;
        Ogre::AnimationState* monstersrAnmations;
        Ogre::AxisAlignedBox monstersBox;
        Ogre::ParticleSystem* _explosion;
        Ogre::SceneNode* _explosionNode;
        float _explosionTime=0;

    };

    int AINumaber;
    std::vector<AIMonster> _AIVector;

    //player
    Ogre::SceneNode* _node;
    Ogre::Camera* _cam;
    Ogre::SceneNode* _camNode;
    Ogre::PolygonMode _PolyMode;
    float _movementspeed;
    bool _moveForward, _moveBackward, _moveLeft, _moveRight;
    bool _pressedBefore;
    Ogre::Entity* _ent;
    Ogre::AnimationState* _aniStateIdle;
    Ogre::AnimationState* _aniStateWalk;
    Ogre::AnimationState* _aniStateAttack;
    Ogre::Vector3 _translateVector;

    //장애물
    Ogre::SceneNode* _houseNode;
    Ogre::AxisAlignedBox* _houseboxes;
    int _numHouses;
    Ogre::AxisAlignedBox _playerBox;
    float minNumber, maxNumber;

    Ogre::SceneManager* _scnMgr;
   
    OgreBites::Slider* _mHpBar;
    OgreBites::Label* _mScoreLabel;

    int PlayerHP;
    int Score;
    float mTimeSinceLastUpdate;


public:
    FianlExamFrameListener(Ogre::SceneManager* scnMgr,Ogre::SceneNode* node, Ogre::Entity* ent, Ogre::SceneNode* camNode, Ogre::Camera* cam,
        Ogre::AnimationState* aniStateIdle, Ogre::AnimationState* aniStateWalk, Ogre::AnimationState* aniStateAttack,
        Ogre::AxisAlignedBox* houseboxes, int numHouses, Ogre::SceneNode* houseNode, OgreBites::Slider* mHpBar, OgreBites::Label* mScoreLabel
        )
        : _node(node), _ent(ent), _camNode(camNode), _cam(cam), _movementspeed(10.0f), _pressedBefore(false),
        _PolyMode(Ogre::PolygonMode::PM_SOLID), _moveForward(false), _moveBackward(false),
        _moveLeft(false), _moveRight(false), _translateVector(Ogre::Vector3::ZERO),
        _aniStateIdle(aniStateIdle), _aniStateWalk(aniStateWalk), _aniStateAttack(aniStateAttack),
        _houseboxes(houseboxes), _numHouses(numHouses), _houseNode(houseNode), minNumber(0.5), maxNumber(2.5), AINumaber(10),
        _scnMgr(scnMgr), _mHpBar(mHpBar), _mScoreLabel(mScoreLabel), PlayerHP(100), Score(0), mTimeSinceLastUpdate(0)
    {
        _aniStateIdle->setLoop(true);
        _aniStateIdle->setEnabled(true);
        _aniStateWalk->setLoop(false);
        _aniStateAttack->setLoop(false);        

        _AIVector.reserve(AINumaber);
        // 적 AI 만들기
        for (int i = 0; i < AINumaber; ++i)
        {
            AIMonster AI;
            CreateMonsters(AI);
            _AIVector.push_back(AI);
        }
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_ESCAPE)
        {
            return false;
        }
        if (evt.keysym.sym == SDLK_w)
        {
            _moveForward = true;
            if (!_aniStateWalk->getEnabled())
            {
                changeAnimationState(_aniStateWalk);
            }
        }
        else if (evt.keysym.sym == SDLK_s)
        {
            _moveBackward = true;
            if (!_aniStateWalk->getEnabled())
            {
                changeAnimationState(_aniStateWalk);
            }
        }
        else if (evt.keysym.sym == SDLK_a)
        {
            _moveLeft = true;
            if (!_aniStateWalk->getEnabled())
            {
                changeAnimationState(_aniStateWalk);
            }
        }
        else if (evt.keysym.sym == SDLK_d)
        {
            _moveRight = true;
            if (!_aniStateWalk->getEnabled())
            {
                changeAnimationState(_aniStateWalk);
            }
        }
        else if (evt.keysym.sym == SDLK_r && !_pressedBefore)
        {
            _pressedBefore = true;
            if (_PolyMode == Ogre::PolygonMode::PM_SOLID)
            {
                _PolyMode = Ogre::PolygonMode::PM_WIREFRAME;
            }
            else if (_PolyMode == Ogre::PolygonMode::PM_WIREFRAME)
            {
                _PolyMode = Ogre::PolygonMode::PM_POINTS;
            }
            else if (_PolyMode == Ogre::PolygonMode::PM_POINTS)
            {
                _PolyMode = Ogre::PolygonMode::PM_SOLID;
            }

            _cam->setPolygonMode(_PolyMode);
        }
        return true;
    }

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == SDLK_w)
        {
            _moveForward = false;
        }
        else if (evt.keysym.sym == SDLK_s)
        {
            _moveBackward = false;
        }
        else if (evt.keysym.sym == SDLK_a)
        {
            _moveLeft = false;
        }
        else if (evt.keysym.sym == SDLK_d)
        {
            _moveRight = false;
        }
        else if (evt.keysym.sym == SDLK_r)
        {
            _pressedBefore = false;
        }

        if (!_moveForward && !_moveBackward && !_moveLeft && !_moveRight)
        {
            changeAnimationState(_aniStateIdle);
        }
        return true;
    }

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override
    {
        float rotX = evt.xrel * -0.001f;

        _node->yaw(Ogre::Radian(rotX));

        return true;
    }

    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override
    {
        if (evt.button == SDL_BUTTON_RIGHT)
        {
            changeAnimationState(_aniStateAttack);

            // 공격 반경 10 설정
            Ogre::AxisAlignedBox boundingBox1 = _ent->getWorldBoundingBox();
            Ogre::Vector3 min = boundingBox1.getMinimum() - Ogre::Vector3(10, -minNumber, 10);
            Ogre::Vector3 max = boundingBox1.getMaximum() + Ogre::Vector3(10, maxNumber, 10);

            boundingBox1.setExtents(min, max);


            for (int i = 0; i < AINumaber; ++i)
            {
                if (_AIVector[i].monsterState == alive)
                {
                    _AIVector[i].monstersBox = _AIVector[i].mMonsters->getWorldBoundingBox();
                    if (boundingBox1.intersects(_AIVector[i].monstersBox))
                    {
                        std::string name = "monster_effect_kill" + std::to_string(i);
                        Ogre::ParticleSystem* explosion = _scnMgr->createParticleSystem(name, "MySample/JetEngine2");
                        Ogre::SceneNode* explosionNode = _scnMgr->getRootSceneNode()->createChildSceneNode(_AIVector[i].mMonstersNode->getPosition());
                        explosionNode->attachObject(explosion);

                        // 몬스터 제거
                        _AIVector[i].mMonstersNode->detachObject(_AIVector[i].mMonsters);
                        _scnMgr->destroyEntity(_AIVector[i].mMonsters);
                        _AIVector[i].mMonsters = nullptr;

                        _AIVector[i]._explosionTime = 3.0f;
                        _AIVector[i]._explosion = explosion;
                        _AIVector[i]._explosionNode = explosionNode;

                        Score += 10;
                
                        _AIVector[i].monsterState = (MonsterState)particle;
                    }
                }
                 
            }


        }
        return true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt) override
    {
        _translateVector = Ogre::Vector3::ZERO;

        if (_moveForward)
        {
            _translateVector.z += 1;
        }
        if (_moveBackward)
        {
            _translateVector.z -= 1;
        }
        if (_moveLeft)
        {
            _translateVector.x += 1;
        }
        if (_moveRight)
        {
            _translateVector.x -= 1;
        }
        

        Ogre::Vector3 newPosition = _node->getPosition() + _translateVector * evt.timeSinceLastFrame * _movementspeed;

        // 현재 위치의 바운딩 박스를 가져옵니다.
        _playerBox = _ent->getWorldBoundingBox(true);

        _playerBox.setMinimumY(_playerBox.getMinimum().y + minNumber);
        _playerBox.setMaximumY(_playerBox.getMaximum().y + maxNumber);


        bool collision = false;
        int houseNumber = 0;

        for (int i = 0; i < _numHouses; ++i)
        {
            if (_playerBox.intersects(_houseboxes[i]))
            {
                //std::cerr << "_houseboxes" << i << std::endl;
                houseNumber = i;
                collision = true;
                break;
            }
        }
        _node->translate(_translateVector * evt.timeSinceLastFrame * _movementspeed, Ogre::Node::TS_LOCAL);

       if(collision)
        {
            Ogre::Vector3 direction = _node->getPosition()- (_houseNode + houseNumber)->getPosition();
            direction.normalise();
            direction.y = 0;

            newPosition = _node->getPosition() - direction * 0.3f;
            _node->setPosition(newPosition);
        }
       

        _aniStateIdle->addTime(evt.timeSinceLastFrame);
        _aniStateWalk->addTime(evt.timeSinceLastFrame);
        _aniStateAttack->addTime(evt.timeSinceLastFrame);

        if (_aniStateWalk->hasEnded() && (_moveForward || _moveBackward || _moveLeft || _moveRight))
        {
            _aniStateWalk->setTimePosition(0);
            _aniStateWalk->setEnabled(true);
        }

        //AI
        for (int i=0; i< AINumaber;++i) //for (auto AIVector : _AIVector) 버그 난다 더미? AIVector생성되서 버그일어남 쓰지마라
        {
            switch(_AIVector[i].monsterState)
            {
            case alive:
            {

                Ogre::Vector3 playerPosition = _node->getPosition();
                Ogre::Vector3 aiPosition = _AIVector[i].mMonstersNode->getPosition();

                Ogre::Vector3 direction = playerPosition - aiPosition;
                float distance = direction.length();
                direction.normalise();

                // AI가 플레이어를 바라보도록 설정
                _AIVector[i].mMonstersNode->lookAt(playerPosition, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);

                _AIVector[i].monstersrAnmations->addTime(evt.timeSinceLastFrame * 5);

                if (_AIVector[i].monstersrAnmations->hasEnded())
                {
                    _AIVector[i].monstersrAnmations->setTimePosition(0);
                    _AIVector[i].monstersrAnmations->setEnabled(true);
                }

                // 일정 거리 이하로 접근하면 멈춤
                if (distance > 0.7f) // 플레이어와의 최소 거리 설정
                {
                    _AIVector[i].mMonstersNode->translate(direction * evt.timeSinceLastFrame * (_movementspeed / 2), Ogre::Node::TS_WORLD);
                }
                // 여기까지는 맞음


                _AIVector[i].monstersBox = _AIVector[i].mMonsters->getWorldBoundingBox();
                if (_AIVector[i].monstersBox.intersects(_playerBox))
                {
                    std::string name = "monster_effect_damge" + std::to_string(i);
                    // 파티클 이펙트 트리거
                    Ogre::ParticleSystem* explosion = _scnMgr->createParticleSystem(name,"MySample/Smoke");
                    Ogre::SceneNode* explosionNode = _scnMgr->getRootSceneNode()->createChildSceneNode(_AIVector[i].mMonstersNode->getPosition());
                    explosionNode->attachObject(explosion);

                    // 몬스터 제거
                    _AIVector[i].mMonstersNode->detachObject(_AIVector[i].mMonsters);
                    _scnMgr->destroyEntity(_AIVector[i].mMonsters);
                    _AIVector[i].mMonsters = nullptr;

                    _AIVector[i]._explosionTime = 3.0f;
                    _AIVector[i]._explosion = explosion;
                    _AIVector[i]._explosionNode = explosionNode;

                    if(PlayerHP>0)
                        PlayerHP -= 10;

                    _AIVector[i].monsterState = (MonsterState)particle;

                }

                break;
            }
 
            case particle:
            {
                if (_AIVector[i]._explosion && _AIVector[i]._explosionTime > 0.0f)
                {
                    _AIVector[i]._explosionTime -= evt.timeSinceLastFrame;
                    if (_AIVector[i]._explosionTime <= 0.0f)
                    {
                        _scnMgr->destroyParticleSystem(_AIVector[i]._explosion);
                        _scnMgr->destroySceneNode(_AIVector[i]._explosionNode);
                        _AIVector[i]._explosion = nullptr;
                        _AIVector[i]._explosionNode = nullptr;
                        _AIVector[i]._explosionTime = rand()%5+ 5;
                        _AIVector[i].monsterState = (MonsterState)daeth;
                    }
                }

                break;
            }
            case daeth:
            {
                if (_AIVector[i]._explosionTime > 0.0f)
                {
                    _AIVector[i]._explosionTime -= evt.timeSinceLastFrame;
                    if (_AIVector[i]._explosionTime <= 0.0f)
                    {
                          CreateMonsters(_AIVector[i]);
                    }

                }

                break;
            }
            default:
                break;
            }            
        }

        mTimeSinceLastUpdate += evt.timeSinceLastFrame;
        if (mTimeSinceLastUpdate >= 0.5f) // 1초마다 업데이트
        {
            mTimeSinceLastUpdate = 0.0f;
            ChnageUI();
        }

        return true;
    }

    void changeAnimationState(Ogre::AnimationState* newState)
    {
        _aniStateIdle->setEnabled(false);
        _aniStateWalk->setEnabled(false);
        _aniStateAttack->setEnabled(false);

        newState->setEnabled(true);
        newState->setTimePosition(0);
    }
    
    void CreateMonsters()
    {
        AIMonster AI;
        AI.monsterState = (MonsterState)alive;
        AI.mMonsters = _scnMgr->createEntity( "ogremonster_man.mesh");
        AI.mMonsters->setCastShadows(true);
        AI.mMonstersNode = _scnMgr->getRootSceneNode()->createChildSceneNode();
        //mMonstersNode = _scnMgr->getRootSceneNode()->createChildSceneNode("monstersNodes");
        AI.mMonstersNode->setPosition(Ogre::Vector3(rand() % 100 - 50, _node->getPosition().y, rand() % 100 - 50));
        AI.mMonstersNode->scale(35, 20, 35);
        //mMonstersNode->yaw(Ogre::Degree(90));
        AI.mMonstersNode->attachObject(AI.mMonsters);


        AI.monstersrAnmations = AI.mMonsters->getAnimationState("walk");
        AI.monstersrAnmations->setLoop(true);
        AI.monstersrAnmations->setEnabled(true);

        AI.mMonstersNode->showBoundingBox(true);
        AI.monstersBox = AI.mMonsters->getBoundingBox();

        _AIVector.push_back(AI);
    }
    void CreateMonsters(AIMonster& AI)
    {
        AI.mMonsters = _scnMgr->createEntity("ogremonster_man.mesh");
        AI.mMonsters->setCastShadows(true);
        AI.mMonstersNode = _scnMgr->getRootSceneNode()->createChildSceneNode();
        //mMonstersNode = _scnMgr->getRootSceneNode()->createChildSceneNode("monstersNodes");
        AI.mMonstersNode->setPosition(Ogre::Vector3(rand() % 100 - 50, _node->getPosition().y, rand() % 100 - 50));
        AI.mMonstersNode->scale(35, 35, 35);
        //mMonstersNode->yaw(Ogre::Degree(90));
        AI.mMonstersNode->attachObject(AI.mMonsters);


        AI.monstersrAnmations = AI.mMonsters->getAnimationState("walk");
        AI.monstersrAnmations->setLoop(true);
        AI.monstersrAnmations->setEnabled(true);

        AI.mMonstersNode->showBoundingBox(true);
        AI.monstersBox = AI.mMonsters->getBoundingBox();
        AI.monsterState = (MonsterState)alive;
    }

    void ChnageUI()
    {
        _mHpBar->setValue(PlayerHP);
        _mScoreLabel->setCaption("Score: " + std::to_string(Score));
    }
};


class FianlExam: public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{
private:
    Ogre::Root* root;
    Ogre::RenderWindow* window;

    Ogre::Camera* cam;
    Ogre::SceneNode* camNode;

    Ogre::SceneNode* _SinbadNode;
    Ogre::Entity* _SinbadEnt;
    Ogre::SceneManager* scnMgr;

    //도시
    Ogre::Entity* city;
    Ogre::SceneNode* cityNode;
    Ogre::AxisAlignedBox cityBox;

    Ogre::Entity* load;
    Ogre::SceneNode* loadNode;

    Ogre::Entity* houses[61];
    Ogre::SceneNode* houseNodes[61];
    Ogre::AxisAlignedBox housebox[61];

    //플레이어
    Ogre::Entity* mplayers;
    Ogre::SceneNode* mplayersNode;
    Ogre::SceneNode* mplayersBoxNode;
    Ogre::AxisAlignedBox mplayersBox;
    Ogre::AnimationState* playerAnmations[3];

    Ogre::Light* playerPointLight;
    Ogre::SceneNode* playerLightNode;

    Ogre::Entity* playerSword[3];
    Ogre::SceneNode* playerSwordNode[3];

    //UI
    Ogre::Overlay* overlay;
    Ogre::OverlaySystem* mOverlaySystem;
    OgreBites::TrayManager* mTrayMgr;

    OgreBites::Slider* mHpBar;
    OgreBites::Label* mScoreLabel;

    SceneType mCurrentScene;
    FianlExamFrameListener* frameListener;
public:
    FianlExam() : OgreBites::ApplicationContext("FianlExam") {
  
    }

    ~FianlExam()  {

    }

    void setup() override
    {
        // 기본 설정 호출
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        root = getRoot();
        Ogre::RenderWindow* window = getRenderWindow();
        scnMgr = root->createSceneManager();

        // OverlaySystem 생성 (이미 생성된 경우 무시)
        if (!Ogre::OverlaySystem::getSingletonPtr())
            mOverlaySystem = new Ogre::OverlaySystem();
        else
            mOverlaySystem = Ogre::OverlaySystem::getSingletonPtr();

        // SceneManager에 OverlaySystem 추가
        scnMgr->addRenderQueueListener(mOverlaySystem);

        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        CreateCamera();
        

        // Overlay 생성
        CreateOverlay();

        // 기본 TrayManager 생성
        mTrayMgr = new OgreBites::TrayManager("InterfaceName", window, this);
        addInputListener(mTrayMgr);

        changeScene();
    }
    void CreateCamera()
    {
        cam = scnMgr->createCamera("MainCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);

        camNode = scnMgr->getRootSceneNode()->createChildSceneNode("CamNode");
        camNode->attachObject(cam);

        //camNode->setPosition(0, 10, 50);
        //camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

        Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
        cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    }

    void changeScene()
    {
        scnMgr->clearScene();
        mTrayMgr->destroyAllWidgets();
        overlay->hide();

        switch (mCurrentScene)
        {
        case SceneType::Start:
        {
            mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Start");
            mTrayMgr->showAll();
            break;
        }
        case SceneType::Main:
        {
            setupMainScene();
            break;
        }
        case SceneType::End:
        {
            Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
                Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "PanelName"));
            panel->setPosition(0.0, 0.0);
            panel->setDimensions(1.0, 1.0);

            Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
                Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "TextArea"));

            textArea->setCaption("GameOver");
            textArea->setMetricsMode(Ogre::GMM_RELATIVE);

            // 중앙에 위치하도록 설정
            textArea->setPosition(0.5 - 0.4, 0.5 - 0.15); // 가운데 정렬을 위해 가로 세로 각각 절반 크기만큼 뺌
            textArea->setDimensions(0.8, 0.3); // 가로 80%, 세로 30% 크기
            textArea->setCharHeight(0.1); // 큰 글자 크기
            textArea->setFontName("SdkTrays/Value");
            textArea->setColour(Ogre::ColourValue::Black);

            panel->addChild(textArea);

            Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("OverlayName");
            overlay->add2D(panel);

            overlay->show();

        }


        }


    }
    void setupMainScene()
    {
        camNode = scnMgr->getRootSceneNode()->createChildSceneNode("CamNode");
        camNode->attachObject(cam);

        CreateLight();

        CreateMap();
        CreatePlayers();

        CreateSkyBox();

        CreateUI();

        CreatFrameListener();
    }


    void CreateMap()
    {
        city = scnMgr->createEntity("city", "ogreThe_City.mesh");
        city->setCastShadows(false);
        cityNode = scnMgr->getRootSceneNode()->createChildSceneNode("cityNode");
        cityNode->scale(4, 1, 4);
        cityNode->attachObject(city);

        load = scnMgr->createEntity("load", "ogreload.mesh");
        load->setCastShadows(false);
        loadNode = cityNode->createChildSceneNode("loadNode");
        loadNode->attachObject(load);

        // 엔티티의 로컬 좌표계에서 바운딩 박스를 얻음
        Ogre::AxisAlignedBox localBoundingBox = load->getBoundingBox();

 
        // 건물 오브젝트 생성
        for (int i = 0; i < 61; ++i)
        {
            Ogre::String name = "ogre" + std::to_string(i + 1) + ".mesh";
            houses[i] = scnMgr->createEntity(name);
            houses[i]->setCastShadows(true);
            //houses[i]->setMaterialName("Ogre_City_Building_NormalMap_Material");
            houseNodes[i] = loadNode->createChildSceneNode("HouseNode" + std::to_string(i));
            houseNodes[i]->attachObject(houses[i]);
            houseNodes[i]->scale(1, 4, 1);
            houseNodes[i]->setPosition(0, -housebox[i].getCorner(Ogre::AxisAlignedBox::FAR_LEFT_BOTTOM).y - 2, 0);
            //houseNodes[i]->setPosition(0, cityNode->getPosition().y - 1, 0);
            houseNodes[i]->showBoundingBox(true);
            
            Ogre::AxisAlignedBox localBoundingBox = houses[i]->getBoundingBox();

            // 월드 변환 매트릭스를 적용하여 월드 좌표계에서 바운딩 박스를 계산
            Ogre::Matrix4 worldTransform = houseNodes[i]->_getFullTransform();
            Ogre::AxisAlignedBox worldBoundingBox;
            worldBoundingBox.merge(worldTransform * localBoundingBox.getMinimum());
            worldBoundingBox.merge(worldTransform * localBoundingBox.getMaximum());

            // 바운딩 박스의 크기를 얻음
            Ogre::Vector3 size = worldBoundingBox.getSize();
            Ogre::Real width = size.x;
            Ogre::Real height = size.y;
            Ogre::Real depth = size.z;

            // 바운딩 박스를 저장
            housebox[i] = worldBoundingBox;
            

        }
    }

    void CreateLight()
    {
        // 메인 라이트 생성
        Ogre::Light* light = scnMgr->createLight("MainLight");
        light->setDiffuseColour(Ogre::ColourValue(0.8, 0.8, 0.8)); // 라이트 강도를 0.8로 설정
        light->setSpecularColour(Ogre::ColourValue(0.5, 0.5, 0.5)); // 스페큘러 강도를 0.5로 설정
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(20, 80, 50);
        lightNode->attachObject(light);

        // 추가 라이트 생성
        Ogre::Light* light1 = scnMgr->createLight("spotLight");
        Ogre::SceneNode* lightNode1 = scnMgr->getRootSceneNode()->createChildSceneNode();
        light1->setType(Ogre::Light::LT_POINT);
        light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
        light1->setSpotlightInnerAngle(Ogre::Degree(35.0f));
        light1->setSpotlightOuterAngle(Ogre::Degree(50.0f));
        lightNode1->setDirection(1, 1, 0);
        lightNode1->setPosition(Ogre::Vector3(100, 200, 0));
        lightNode1->attachObject(light1);
    }

    void CreatePlayers()
    {
        mplayers = scnMgr->createEntity("player", "ogreTorso.mesh");
        mplayers->setCastShadows(true);
        mplayersNode = scnMgr->getRootSceneNode()->createChildSceneNode("PlayersNode");
        mplayersNode->attachObject(mplayers);
        mplayersNode->setPosition(0, cityNode->getPosition().y+1, 0);
        //mplayersNode->setScale(5, 5, 5);

        playerAnmations[0] = mplayers->getAnimationState("wait");
        playerAnmations[0]->setLoop(false);
        playerAnmations[0]->setEnabled(false);
        playerAnmations[1] = mplayers->getAnimationState("walk");
        playerAnmations[1]->setLoop(false);
        playerAnmations[1]->setEnabled(false);
        playerAnmations[2] = mplayers->getAnimationState("atteck");
        playerAnmations[2]->setLoop(false);
        playerAnmations[2]->setEnabled(false);

        playerPointLight = scnMgr->createLight("playerPointLight");
        playerPointLight->setType(Ogre::Light::LT_POINT);
        playerPointLight->setDiffuseColour(0.3f, 0.3f, 0.3f);
        playerPointLight->setSpecularColour(0.3f, 0.3f, 0.3f);

        playerLightNode = mplayersNode->createChildSceneNode("playerLightNode");
        playerLightNode->attachObject(playerPointLight);
        playerLightNode->setPosition(Ogre::Vector3(-100, 150, 250));

        for (int i = 0; i < 3; ++i)
        {
            Ogre::String name = "ogreTorso_Sword" + Ogre::StringConverter::toString(i);
            Ogre::String header = name + ".mesh";
            playerSword[i] = scnMgr->createEntity(name, header);
            playerSwordNode[i] = mplayersNode->createChildSceneNode(name);
            playerSwordNode[i]->attachObject(playerSword[i]);
        }
        

        mplayersNode->showBoundingBox(true);
        mplayersBox = mplayers->getWorldBoundingBox();
        
        Ogre::Vector3 min = mplayersBox.getMinimum();
        Ogre::Vector3 max = mplayersBox.getMaximum();

        min.y += 0.5;
        max.y += 2.5;

        Ogre::ManualObject* manual = scnMgr->createManualObject("PlayerBoundingBox");
        manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

        manual->position(min.x, min.y, min.z); manual->position(max.x, min.y, min.z);
        manual->position(min.x, min.y, min.z); manual->position(min.x, max.y, min.z);
        manual->position(min.x, min.y, min.z); manual->position(min.x, min.y, max.z);
        manual->position(max.x, max.y, max.z); manual->position(min.x, max.y, max.z);
        manual->position(max.x, max.y, max.z); manual->position(max.x, min.y, max.z);
        manual->position(max.x, max.y, max.z); manual->position(max.x, max.y, min.z);
        manual->position(min.x, max.y, min.z); manual->position(max.x, max.y, min.z);
        manual->position(min.x, max.y, min.z); manual->position(min.x, max.y, max.z);
        manual->position(min.x, min.y, max.z); manual->position(max.x, min.y, max.z);
        manual->position(min.x, min.y, max.z); manual->position(min.x, max.y, max.z);
        manual->position(max.x, min.y, min.z); manual->position(max.x, max.y, min.z);
        manual->position(max.x, min.y, min.z); manual->position(max.x, min.y, max.z);

        manual->end();

        mplayersBoxNode = mplayersNode->createChildSceneNode("BoundingBoxNode");
        mplayersBoxNode->attachObject(manual);


        // 카메라 노드를 플레이어 노드에 연결
        scnMgr->getRootSceneNode()->removeChild(camNode);
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        //camNode->setPosition(0, 5, 8); // 플레이어 뒤의 위치 설정
        camNode->setPosition(0, 3, -9); // 플레이어 뒤의 위치 설정
        camNode->lookAt(Ogre::Vector3(0, 1, 0), Ogre::Node::TS_WORLD);
        camNode->setScale(1,1, 1);
        camNode->roll(Ogre::Degree(180));
   
        mplayersNode->addChild(camNode);
    }

    void CreatFrameListener()
    {
        frameListener = new FianlExamFrameListener(scnMgr ,mplayersNode, mplayers, camNode, cam, 
            playerAnmations[0], playerAnmations[1], playerAnmations[2], housebox, 61, houseNodes[0], mHpBar, mScoreLabel
        );
        root->addFrameListener(frameListener);
        addInputListener(frameListener);
    }

    void CreateOverlay()
    {
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

        // 이미 정의된 OverlayElement 가져오기
        Ogre::OverlayElement* panel = overlayManager.getOverlayElement("SdkTrays/Tray");

        // 패널 설정
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(10, 10);
        panel->setDimensions(300, 120);

        // Overlay 생성 및 추가
        overlay = overlayManager.create("myOverlay");
        overlay->add2D(static_cast<Ogre::OverlayContainer*>(panel));
        overlay->show();
    }

    void CreateUI()
    {
        // HP 바 슬라이더 생성
        mHpBar = mTrayMgr->createThickSlider(OgreBites::TL_TOPLEFT, "HPBar", "HP", 300, 100, 0, 100, 100);
        mHpBar->setValue(100); // 초기 HP를 100으로 설정
        
        // 스코어 라벨 생성
        mScoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "ScoreLabel", "Score: 0", 200);

        mTrayMgr->showAll();
    }

    void CreateSkyBox()
    {
        //scnMgr->setSkyBox(true, "Examples/SteveCubeSkyBox", 600, true);
        Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
        getRenderWindow()->getViewport(0)->setBackgroundColour(fadeColour);

        scnMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
        scnMgr->setFog(Ogre::FOG_EXP, fadeColour, 0.002);
        scnMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.002);
    }

    void buttonHit(OgreBites::Button* button) override
    {
        if (button->getName() == "MyButton")
        {
            mCurrentScene = SceneType::Main;
            changeScene();
        }
    }

    void sliderMoved(OgreBites::Slider* slider) override
    {
        if (slider->getName() == "HPBar")
        {
            if (slider->getValue() <= 0&& mCurrentScene== SceneType::Main)
            {
                mCurrentScene = SceneType::End;
                changeScene();

                if (frameListener != nullptr)
                {
                    root->removeFrameListener(frameListener);
                    removeInputListener(frameListener); 
                    delete frameListener;
                    frameListener = nullptr;
                }
            }
        }
    }
};

int main(int argc, char** argv)
{
    try {
        FianlExam app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();

    }
    catch (Ogre::Exception& e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}