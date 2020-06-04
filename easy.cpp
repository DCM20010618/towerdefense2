#include "easy.h"
#include "ui_easy.h"
#include <mainwindow.h>
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <plistreader.h>

static const int TowerCost = 200;

Easy::Easy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Easy)
    , m_waves(0)
    , m_playerHp(1)
    , m_playrGold(400)
    , m_gameEnded(false)
    , m_gameWin(false)
{
    ui->setupUi(this);
    setFixedSize(1280,720);
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

Easy::~Easy()
{
    delete ui;
}

void Easy::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(81, 242),
        QPoint(236, 47),
        QPoint(336, 47),
        QPoint(436, 47),
        QPoint(536, 47),
        QPoint(304, 294),
        QPoint(404, 294),
        QPoint(504, 294),
        QPoint(860, 225),
        QPoint(760, 225),
        QPoint(647, 461),
        QPoint(747, 461),
        QPoint(847, 461),
        QPoint(947, 461),
        QPoint(1013, 86),
        QPoint(1115, 328)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void Easy::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
     painter.drawPixmap(0,0,1280,720, QPixmap("://images/easypattern.jpg"));
    if (m_gameEnded || m_gameWin)
    {

        QString text = m_gameEnded ? "Defeat!!!" : "Victory!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        QFont font1("宋体",64,QFont::Bold, true) ;
        painter.setFont(font1);
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    int i;
             for(i=0;i<=15;++i)
             {
                 painter.drawPixmap(m_towerPositionsList[i].Pos11x(),m_towerPositionsList[i].Pos11y(),102,102,QPixmap("://images/base.png"));
             }

    foreach (const Tower *tower, m_towersList)
        tower->draw(&painter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
    //    wayPoint->draw(&painter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

    //drawHP(&painter);
    drawPlayerGold(&painter);

}

void Easy::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {

            m_playrGold -= TowerCost;
            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

bool Easy::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void Easy::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

/*void Easy::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}*/

void Easy::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    QFont font1("宋体",32,QFont::Bold, true) ;
    painter->setFont(font1);
    painter->drawText(QRect(40, 5, 1000, 1000), QString(" %1").arg(m_playrGold));
    painter->drawPixmap(0,0,62,62,QPixmap("://images/money.png"));
}

void Easy::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void Easy::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

AudioPlayer *Easy::audioPlayer() const
{
    return m_audioPlayer;
}


void Easy::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1239, 254));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1044, 261));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(1031, 399));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(674,405 ));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(663,233 ));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(242,234 ));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(236,426));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(40,423 ));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
}



void Easy::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void Easy::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void Easy::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void Easy::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void Easy::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void Easy::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);
    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

bool Easy::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}


QList<Enemy *> Easy::enemyList() const
{
    return m_enemyList;
}

void Easy::gameStart()
{
    loadWave();
}
