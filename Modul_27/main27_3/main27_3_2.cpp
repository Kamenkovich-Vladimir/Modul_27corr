#include <iostream>
#include <ctime>
#include <string>
#include <vector>

class Branch
{
public:
	//Конструктор для дерева
	Branch(Branch* inParent, std::vector<Branch*> inChildVec) : parent(inParent), childVec(inChildVec) {}
	//Конструктор для большой ветви
	Branch(Branch* inParent, std::string inName, std::vector<Branch*> inChildVec) :
		parent(inParent), name(inName), childVec(inChildVec) {}
	//Конструктор для средней ветви (если малыми ветвями пренебрегаем)
	Branch(Branch* inParent, std::string inName) : parent(inParent), name(inName) {}

	std::string getName(Branch* branch) {	//Возвращает имя эльфа в доме на ветви
		return branch->name;
	}
	//Возвращает подчинённую ветвь по её индексу в векторе
	Branch* getChild(int index)
	{
		if (this == nullptr) return nullptr;
		if (index < 0) return nullptr;
		if (index >= childVec.size()) return nullptr;
		return this->childVec[index];
	}
	//Возвращает количество соседей на большой ветви соответствующего дерева
	int getNeighborsNumber(Branch* branch)
	{
		int number = 0;

		for (int j = 0; j < branch->childVec.size(); j++) {
			if (getName(branch->childVec[j]) != "None") {
				number++;
			}
			for (int k = 0; k < branch->childVec[j]->childVec.size(); k++) {
				if (getName(branch->childVec[j]->childVec[k]) != "None") {
					number++;
				}
			}
		}
		return number - 1;		//Уберем искомого эльфа из списка соседей
	}
	//Добавляет в вектор дочерних ветвей новую ветвь
	void branchAdd(Branch* branch, int i)
	{
		this->childVec.push_back(branch);
	}
	//Возвращает флаг в случае нахождения на большой ветви эльфа с нужным именем
	bool elfFind(std::string elfName, Branch* branch)
	{
		for (int j = 0; j < branch->childVec.size(); j++) {
			if (getName(branch->childVec[j]) == elfName) {
				return true;
			}
			else {
				for (int k = 0; k < branch->childVec[j]->childVec.size(); k++) {
					if (getName(branch->childVec[j]->childVec[k]) == elfName)
						return true;
				}
			}
		}
		return false;
	}
	void cleaning(Branch* branch)
	{
		for (int j = 0; j < branch->childVec.size(); j++) {
			for (int k = 0; k < branch->childVec[j]->childVec.size(); k++) {
				delete branch->getChild(j)->getChild(k);
			}
			delete branch->getChild(j);
		}
		delete branch;
	}
private:
	Branch* parent = nullptr;
	std::vector<Branch*> childVec;
	std::string name = "None";
};

int main()
{
	std::cout << "***************** Elf's village *****************\n\n";

	std::srand(time(0));
	std::string elfName;				//Имя эльфа в доме или None
	std::vector<Branch*> treeVec;		//Вектор, содержащий деревья - деревня эльфов

	for (int i = 0; i < 5; i++) {		//Формирование деревни эльфов

		int bigBranchCount = rand() % 3 + 3;	//Получим случайным образом количество больших ветвей на дереве
		std::vector<Branch*> bigBranchVec;		//Вектор, содержащий большие ветви дерева
		Branch* tree = new Branch(nullptr, bigBranchVec);	//Инициализация дерева
		std::cout << "\nLet's populate " << i + 1 << " tree:\n";
		std::srand(time(0));
		for (int j = 0; j < bigBranchCount; j++) {
			std::vector<Branch*> midBranchVec;	//Вектор, содержащий средние ветви на большой ветви
			int midBranchCount = rand() % 2 + 2;	//Получим случайным образом количество средних ветвей на большой ветви
			std::cout << "Enter elf's name in house on " << j + 1 << " big branch: ";
			std::cin >> elfName;					//Определим эльфа на заселение в дом на большой ветви
			Branch* bigBranch = new Branch(tree, elfName, midBranchVec);	//Инициализация большой ветви
			tree->branchAdd(bigBranch, i);			//Добавим в вектор больших ветвей дерева инициализированную ветвь
			for (int k = 0; k < midBranchCount; k++) {
				std::cout << "Enter elf's name in house on " << k + 1 << " middle branch of " << j + 1 << " big branch: ";
				std::cin >> elfName;				//Определим эльфа на заселение в дом на средней ветви
				Branch* midBranch = new Branch(bigBranch, elfName);			//Инициализация средней ветви
				bigBranch->branchAdd(midBranch, j);	//Добавим в вектор средних ветвей большой ветви дерева инициализированную ветвь
			}
		}
		treeVec.push_back(tree);		//Добавим сформированное и заселенное эльфами дерево в вектор деревьев
	}

	//Организуем поиск эльфа с заданным именем в деревне
	std::cout << "\n\nEnter the name of the elf for whom we will be looking for neighbors: ";
	std::cin >> elfName;
	bool elfFound = false;
	for (int i = 0; i < 5; i++) {
		Branch* branch = treeVec[i];	//Поищем эльфа на каждом из деревьев в деревне
		elfFound = branch->elfFind(elfName, branch);
		if (elfFound) {					//Если нашли, посчитаем его соседей по большой ветви
			int number = branch->getNeighborsNumber(branch);
			std::cout << "Neighbors number - " << number;
			std::cout << std::endl << std::endl;
			break;
		}
	}
	if (!elfFound)						//Если нет - то и "суда нет"
		std::cout << "Elf " << elfName << " is not found\n\n";
	std::cout << std::endl << std::endl;

	//Соберем мусор
	for (int i = 0; i < 5; i++) {
		treeVec[i]->cleaning(treeVec[i]);
	}
}