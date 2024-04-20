#include <iostream>
#include <ctime>
#include <cassert>
#include <string>
#include <vector>

enum tipeTask {
	A, B, C
};

class Person
{
public:
	Person(std::string inName, bool inBusy) : name(inName), busy(inBusy){}
	std::string getName() {
		return name;
	}
	bool getBusy() {
		return busy;
	}
	void setBusy() {
		busy = true;
	}
private:
	std::string name = "Unknown";       //Имя
	bool busy = false;					//По умолчанию сотрудник не занят выполнением задачи
};
class Chief : public Person
{
public:
	Chief(std::string name, bool busy) : Person(name, busy) {}
};
class Manager : public Person
{
public:
	Manager(std::string name, bool busy) : Person(name, busy) {
	}
};
class Worker : public Manager
{
public:
	Worker(std::string name, bool busy) : Manager(name, busy) {}
};

class Team
{
public:
	Worker* getWorkerAt(int index)
	{
		if (this == nullptr) return nullptr;
		if (index < 0) return nullptr;
		if (index >= workers.size()) return nullptr;
		return this->workers[index];
	}
	void addWorker(Worker* worker) {
		workers.push_back(worker);
	}
	int getWorkerCount()
	{
		return workers.size();
	}
	Manager* getManager()
	{
		return manager;
	}
	Team(class Company* inCompany, class Manager* inManager) : company(inCompany), manager(inManager)
	{
		assert(inCompany != nullptr);
	}

	int getNumber();	//А вдруг пригодится?
private:
	class Company* company = nullptr;
	std::vector<Worker*> workers;	//Вектор рабочих в команде
	Manager* manager = nullptr;		//Менеджер команды
};


class Company 
{
public:
	Team* getTeamAt(int index)
	{
		if (this == nullptr) return nullptr;
		if (index < 0) return nullptr;
		if (index >= teams.size()) return nullptr;
		return this->teams[index];
	}
	int getTeamCount()
	{
		return teams.size();
	}
	void addTeam(Team* team) {
		teams.push_back(team);
	}
	Chief* getChief()
	{
		return chief;
	}
	bool getChiefBusy() {			//Проверим занятость всех рабочих компании
		bool chiefBusy = false;
		for (int i = 0; i < this->getTeamCount(); i++) {
			if (!this->getTeamAt(i)->getManager()->getBusy()) {
				chiefBusy = false;
				break;
			}
			else
				chiefBusy = true;
		}
		return chiefBusy;
	}
	Company(int inTeamCount, class Chief* inChief, int inWorkerCount) : teamCount(inTeamCount),  chief(inChief)
	{
		
	}
private:
	int teamCount = 0;		//Количество команд в компании
	std::vector <Team*> teams;	//Вектор команд
	Chief* chief = nullptr;		//Шеф компании
};

int Team::getNumber()			//А вдруг пригодится?
{
	for (int i = 0; i < company->getTeamCount(); ++i)
	{
		Team* team = company->getTeamAt(i);
		if (team == this) return i;
	}
	assert(false);
}

int main()
{
	std::cout << "***************** Simulation of the company's work *****************\n\n";

	int teamsCount;

	std::cout << "Enter the number of teams in the company: ";
	std::cin >> teamsCount;
	Chief* chief = new Chief("Boss", false);	//Инициализация шефа компании
	Company* company = nullptr;
	company = new Company(teamsCount, chief, 0);	//Инициализация компании

	for (int i = 0; i < teamsCount; i++) {
		int workerCount;
		std::cout << "Enter the number of workers in the " << i + 1 << " team: ";
		std::cin >> workerCount;
		Manager* manager = new Manager(std::to_string(i), false);	//Инициализация менеджера команды
		Team* team = new Team(company, manager);		//Инициализация каждой команды в компании
		company->addTeam(team);		//Добавляем в вектор компании новую команду
		for (int j = 0; j < workerCount; j++) {
			Worker* worker = new Worker(std::to_string(j), false);	//Инициализация каждого рабочего команды
			team->addWorker(worker);//Добавляем в вектор команды нового рабочего
		}
	}
	bool chiefBusy = false;
	while (!chiefBusy) {
		int strategicTask;
		std::cout << "Enter the company's strategic objective (integer): ";
		std::cin >> strategicTask;
		std::cout << std::endl;
		for (int i = 0; i < teamsCount; i++) {					//Для каждой команды:
			srand(strategicTask + i);						//- посеем зерно :)
			Team* currentTeam = company->getTeamAt(i);

			if (currentTeam->getManager()->getBusy()) continue;	//- если в команде все заняты, переходим к следующей

			int workerCount = currentTeam->getWorkerCount();
			int tasksCount = std::rand() % (workerCount + 1);	//- случайным образом формируем количество задач
			std::cout << "Manager, name: " << i + 1 <<
				" get " << tasksCount << " tasks!\n\n";
			int t = 0;
			for (int j = 0; j < workerCount; j++) {				//Для каждого рабочего в команде:
				if (t >= tasksCount) break;						//- при наличии свободных задач для постановки
				else {
					Worker* currentWorker = currentTeam->getWorkerAt(j);
					if (currentWorker->getBusy()) {				//- проверим не занят ли он уже
						continue;								//- если занят, переходим к следующему
					}
					else {
						t += 1;									//- если свободен, назначаем ему случайным образом
						currentWorker->setBusy();
						int intTask = std::rand() % 3;			//выбранную задачу из перечисления
						switch (intTask) {
						case tipeTask::A:
							std::cout << "\tWorker, name: " << j + 1 <<
								" received task " << "A" << "!\n\n";
							break;
						case tipeTask::B:
							std::cout << "\tWorker, name: " << j + 1 <<
								" received task " << "B" << "!\n\n";
							break;
						case tipeTask::C:
							std::cout << "\tWorker, name: " << j + 1 <<
								" received task " << "C" << "!\n\n";
							break;
						default:
							break;
						}
					}
				}
				if (j == workerCount - 1) {						//Если все рабочие команды заняты, сообщаем
					currentTeam->getManager()->setBusy();		//руководителю компании об этом
					std::cout << company->getChief()->getName() << "! Manager, name: " << i + 1 << " is busy!\n\n";
				}
			}
		}	
		chiefBusy = company->getChiefBusy();					//Если все рабочие всех команд заняты,
	}															//сообщаем руководителю компании и завершаем работу
	std::cout << company->getChief()->getName() << "! Workers of all teams are busy!\n\n";
	for (int i = 0; i < company->getTeamCount(); i++) {
		Team* currentTeam = company->getTeamAt(i);
		delete currentTeam->getManager();
		for (int j = 0; j < currentTeam->getWorkerCount(); j++) {
			delete currentTeam->getWorkerAt(j);
		}
		delete currentTeam;
	}
	delete company;
	delete chief;
}