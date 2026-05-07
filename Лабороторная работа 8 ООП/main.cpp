#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Owner.h"
#include "Property.h"
#include "Apartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include "PropertySimpleFactory.h"

void addOwners(std::vector<Owner*>& owners);

int main()
{
    std::vector<Owner*> owners;
    addOwners(owners);
    setlocale(LC_ALL, "RU");

    enum { exit, addProperty, deleteProperty, addOwner, deleteOwner, jsonRead, jsonWrite };
    enum { apartment, car, countryhouse };

    int choice;

    while (true)
    {
        std::cout << "1. Добавить собственность\n"
            << "2. Удалить собственность\n"
            << "3. Добавить владельца\n"
            << "4. Удалить владельца\n"
            << "5. Считать данные и Json файла\n"
            << "6. Записать данные в Json файл\n"
            << "0. Выход\n";
        std::cin >> choice;

        while (choice < 0 || choice > 6)
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Введите число от 0 до 4: ";
            std::cin >> choice;
        }

        switch (choice)
        {
        case addProperty:
        {
            if (owners.empty()) {
                std::cout << "Нет владельцев! Сначала добавьте владельца.\n";
                break;
            }

            size_t Size = owners.size();
            std::cout << "Выберите владельца которому хотите добавить собственность:" << std::endl;
            for (size_t i = 0; i < Size; ++i)
                std::cout << i + 1 << " - " << owners[i]->getFullname() << std::endl;

            int OwnerIND;
            std::cout << "Выберите номер владельца: ";
            std::cin >> OwnerIND;

            while (OwnerIND < 1 || OwnerIND > Size)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер владельца: ";
                std::cin >> OwnerIND;
            }

            int PropertyType;
            std::cout << "1. Квартира\n"
                << "2. Автомобиль\n"
                << "3. Загородный дом\n";
            std::cin >> PropertyType;

            while (PropertyType < 1 || PropertyType > 3)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер: ";
                std::cin >> PropertyType;
            }

            switch (PropertyType - 1)
            {
            case apartment:
            {
                double worth_ap, square;
                std::cout << "Введите стоимость и размер квартиры: ";
                std::cin >> worth_ap >> square;
                owners[OwnerIND - 1]->addProperty(new Apartment(worth_ap, square));
                break;
            }
            case car:
            {
                double worth_car, horsepower;
                std::cout << "Введите стоимость и лошадиные силы: ";
                std::cin >> worth_car >> horsepower;
                owners[OwnerIND - 1]->addProperty(new Car(worth_car, horsepower));
                break;
            }
            case countryhouse:
            {
                double worth_ch, dist;
                std::cout << "Введите стоимость и расстояние от города: ";
                std::cin >> worth_ch >> dist;
                owners[OwnerIND - 1]->addProperty(new CountryHouse(worth_ch, dist));
                break;
            }
            }
            break;
        }
        case deleteProperty:
        {
            if (owners.empty()) {
                std::cout << "Нет владельцев!\n";
                break;
            }

            size_t size = owners.size();
            std::cout << "Выберите владельца у которого хотите удалить собственность:" << std::endl;
            for (size_t i = 0; i < size; ++i)
                std::cout << i + 1 << " - " << owners[i]->getFullname() << std::endl;

            int ownerIND;
            std::cin >> ownerIND;

            while (ownerIND < 1 || ownerIND > size)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер владельца: ";
                std::cin >> ownerIND;
            }

            std::vector<Property*> props = owners[ownerIND - 1]->getProperties();

            if (props.empty()) {
                std::cout << "У этого владельца нет собственности для удаления!\n";
                break;
            }

            std::cout << "Выберите собственность для удаления:" << std::endl;
            for (size_t i = 0; i < props.size(); ++i)
                std::cout << i + 1 <<" - " << props[i]->getProp() << std::endl;

            int propertyType;
            std::cin >> propertyType;

            while (propertyType < 1 || propertyType > props.size())
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер собственности: ";
                std::cin >> propertyType;
            }

            owners[ownerIND - 1]->removeProperty(props[propertyType - 1]);
            break;
        }
        case addOwner:
        {
            std::string name, inn;
            std::cout << "Введите ФИО владельца: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите ИНН (12 цифр): ";
            std::cin >> inn;
            owners.push_back(new Owner(name, inn));
            break;
        }
        case deleteOwner:
        {
            if (owners.empty()) {
                std::cout << "Нет владельцев для удаления!\n";
                break;
            }

            size_t size_own = owners.size();
            std::cout << "Выберите владельца которого хотите удалить:" << std::endl;
            for (size_t i = 0; i < size_own; ++i)
                std::cout << i + 1 << " - " << owners[i]->getFullname() << std::endl;

            int IND;
            std::cout << "Выберите номер владельца: ";
            std::cin >> IND;

            while (IND < 1 || IND >size_own)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер владельца: ";
                std::cin >> IND;
            }

            delete owners[IND - 1];
            owners.erase(owners.begin() + IND - 1);
            break;
        }
        case jsonRead:
        {
            std::string json_head;
            std::cout << "Напишите название файла из которого нужно взять данные:" << std::endl;
            std::cin.ignore();
            std::getline(std::cin, json_head);
            std::ifstream in(json_head);
            while (!in.is_open())
            {
                std::cin.clear();
                //std::cin.ignore();
                if (json_head.empty()) {
                    std::clog << "Имя выходного файла не может быть пустым" << std::endl;
                    std::getline(std::cin, json_head);
                    std::ifstream in(json_head);
                }
                else {
                    std::clog << "Некорректно введено название файла, пожалуйта попробуйте еще раз!" << std::endl;
                    std::getline(std::cin, json_head);
                    std::ifstream in(json_head);
                }
            }

            nlohmann::json input_json;
            in >> input_json;
            //мб рассмотреть случай когда плохо спарсилось

            in.close();
            if (!input_json.contains("fullname")) {
                std::clog << "В JSON отсутствует обязательное поле 'fullname'" << std::endl;
                std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                break;
            }
            
            if (!input_json.contains("inn")) {
                std::clog << "В JSON отсутствует обязательное поле 'inn'" << std::endl;
                std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                break;
            }
            if (!input_json.contains("properties")) {
                std::clog << "В JSON отсутствует обязательное поле 'properties'" << std::endl;
                std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                break;
            }
            if (!input_json["properties"].is_array()){
                std::clog << "Поле 'properties' должно быть массивом" << std::endl;
                std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                break;
            }
            std::string inn = input_json["inn"];
            if (inn.length() != 12) {
                std::clog << "ИНН должен содержать ровно 12 цифр" << std::endl;
                std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                break;
            }
            for (char c : inn) {
                if (!isdigit(c)) {
                    std::clog << "ИНН должен содержать только цифры" << std::endl;
                    std::cout << "Пользователь не был добавлен, так как условия выполнены не полностью" << std::endl;
                    break;
                }
            }
            Owner* json_owner = new Owner();
            json_owner->fromJson(input_json);
            owners.push_back(json_owner);
            std::cout << "Владелец успешно добавлен!" << std::endl;
            break;
        }
        case jsonWrite:
        {
            size_t size_own = owners.size();
            std::string output_file;
            std::cout << "Выберите владельца, данные которого вы хотите вынести в json-файл:" << std::endl;
            for (size_t i = 0; i < size_own; ++i)
                std::cout << i + 1 << " - " << owners[i]->getFullname() << std::endl;
            int owner_choice;
            std::cin >> owner_choice;
            while (owner_choice < 1 || owner_choice > size_own)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Выберите номер владельца: " << std::endl;
                std::cin >> owner_choice;
            }
            nlohmann::json output_json = owners[owner_choice - 1]->toJson();
            std::cout << "Напишите файл в который будет записываться данные об имуществе этого владельца:" << std::endl;
            std::cin.ignore();
            std::getline(std::cin, output_file);
            std::ofstream out(output_file);
            while (!out.is_open())
            {
                std::cin.clear();
                //std::cin.ignore();
                if (output_file.empty()) {
                    std::clog << "Имя файла не может быть пустым" << std::endl;
                    std::getline(std::cin, output_file);
                    std::ofstream out(output_file);
                }
                else {
                    std::clog << "Некорректно введено название файла, пожалуйта попробуйте еще раз!" << std::endl;
                    std::getline(std::cin, output_file);
                    std::ofstream out(output_file);
                }
            }
            out << output_json.dump(4);
            out.close();
            std::cout << "Данные о имуществе владельца записаны!" << std::endl;
            break;
        }
        case exit:
        {
            return 0;
        }
        }
    }
}

void addOwners(std::vector<Owner*>& owners) {
    Owner* own1 = new Owner("KRYAGHKIN ZAGAR OLEGOVICHSH", "123456789012");
    own1->addProperty(new Apartment(5000000, 80));
    own1->addProperty(new Car(1200000, 150));
    own1->addProperty(new CountryHouse(4000000, 50));
    own1->addProperty(new Apartment(8000000, 110));
    owners.push_back(own1);

    Owner* own2 = new Owner("John Homelander Patriot", "234567890123");
    own2->addProperty(new Apartment(15000000, 150));
    own2->addProperty(new Car(6000000, 300));
    own2->addProperty(new Car(900000, 80));
    own2->addProperty(new CountryHouse(7000000, 25));
    owners.push_back(own2);

    Owner* own3 = new Owner("Allen the Allen", "345678901234");
    own3->addProperty(new Car(5000000, 180));
    own3->addProperty(new Apartment(4500000, 65));
    own3->addProperty(new CountryHouse(12000000, 100));
    own3->addProperty(new Apartment(3000000, 50));
    owners.push_back(own3);
}