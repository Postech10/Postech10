- BattleObject
enemy�� tower�� battleobject�� �Ѵ�. enemy�� tower��
���⼭ ��ӹ޴� Ŭ������ �ȴ�.
AttackRange : ���ݹ����� ��Ÿ����.
Target : ���� Target���� ���� Item�� ��Ÿ����.
HasTarget : ���� Target�� �ִ��� ������ �Ǵ��Ѵ�.
Hp : ü��
DefensivePower : ����
Attackable : ���� ���� ����
SetTarget : Ÿ���� set�ϴ� method
Attack : ���״�� �����ϴ� method
CalcDistance : Target������ �Ÿ��� ����Ѵ�.
IsHitBy : �޾ƿ� int���ڿ� ���� ü���� ��´�.
GetHp : Hp�� return

-Tower
�⺻������ normal tower�̸� ���� tower�� �̷κ��� ��ӹ޴´�.
TargetNum : Ÿ������ ���Ҽ� �ִ� Ÿ���� ��
towercode : tower�� ������ ���ϴ� towercode
upgrade : tower upgrade method
fuseTower : fusion of tower

-Bullet
Normal Tower�� �ƴ϶� ������ �̿�� �� �ִ� Tower����
�߻��ϴ� ����ü�� Ŭ����
move : Bullet�� enemy�� ���� �����̴� method�̸�, �ε���������
action���� �� ����

-���� Tower
Normal tower�κ��� ���� ��� ����� �޽�带 ��ӹ޾Ƽ�
Ŭ������ �̷� �� ������ ���ݹ���� �ٸ��� ������
Attack method�� overriding?
Ư��, SteveJobs�� IncreaseMoney��� method�� ����
(������ �����ΰ� ������ ���ϰ� �����ϹǷ�)

-���� Bullet �Ǵ� Laser
���� Bullet���� ��ӹ�����������, Bullet�� move method�ۿ�
������, Bullet�� enemy�� �浹������ action�� �������� �ʹ� �޶�
�׳� ��ӹ��� �ʰ� ���� Class�� ������̴�.