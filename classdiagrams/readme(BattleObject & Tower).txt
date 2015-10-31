- BattleObject
enemy와 tower를 battleobject라 한다. enemy와 tower는
여기서 상속받는 클래스가 된다.
AttackRange : 공격범위를 나타낸다.
Target : 현재 Target으로 정한 Item을 나타낸다.
HasTarget : 현재 Target이 있는지 없는지 판단한다.
Hp : 체력
DefensivePower : 방어력
Attackable : 공격 가능 여부
SetTarget : 타겟을 set하는 method
Attack : 말그대로 공격하는 method
CalcDistance : Target까지의 거리를 계산한다.
IsHitBy : 받아온 int인자에 따라 체력이 닳는다.
GetHp : Hp를 return

-Tower
기본적으로 normal tower이며 각종 tower는 이로부터 상속받는다.
TargetNum : 타겟으로 정할수 있는 타겟의 수
towercode : tower의 종류를 뜻하는 towercode
upgrade : tower upgrade method
fuseTower : fusion of tower

-Bullet
Normal Tower뿐 아니라 적절히 이용될 수 있는 Tower들이
발사하는 투사체의 클래스
move : Bullet이 enemy를 향해 움직이는 method이며, 부딪혔을때의
action까지 다 구현

-각종 Tower
Normal tower로부터 거의 모든 멤버와 메쏘드를 상속받아서
클래스를 이룰 수 있지만 공격방식이 다르기 때문에
Attack method만 overriding?
특히, SteveJobs는 IncreaseMoney라는 method가 있음
(가만히 세워두고 공격은 안하고 공격하므로)

-각종 Bullet 또는 Laser
원래 Bullet에서 상속받으려했으나, Bullet은 move method밖에
없으며, Bullet이 enemy와 충돌했을시 action이 종류별로 너무 달라
그냥 상속받지 않고 각각 Class를 만들것이다.