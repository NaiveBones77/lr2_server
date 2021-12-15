#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include "Conversion.h"
#include "protocol.h"
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")


Conversion conv;

#define PORT 12346
#pragma warning(disable: 4996)


using namespace std::chrono_literals;
using namespace std;

int main() {

	char buff[4];


	printf("UDP DEMO echo-Server\n");

	// шаг 1 - подключение библиотеки 
	if (WSAStartup(0x202, (WSADATA*)&buff[0]))
	{
		printf("WSAStartup error: %d\n",
			WSAGetLastError());
		return -1;
	}

	// шаг 2 - создание сокета
	SOCKET my_sock;
	my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET)
	{
		printf("Socket() error: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	// шаг 3 - связывание сокета с локальным адресом 
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(PORT);

	if (bind(my_sock, (sockaddr*)&local_addr,
		sizeof(local_addr)))
	{
		printf("bind error: %d\n", WSAGetLastError());
		closesocket(my_sock);
		WSACleanup();
		return -1;
	}

	FILE* ofile;
	const char* name = "result.txt";
	fopen_s(&ofile, name, "w");		// файл с результатом
	const char* f_header = "%-34s %-34s %-25s";
	fprintf_s(ofile, f_header, "Время приема сообщения", "Имя параметра", "Значение");

	int i;
	int x1 = conv.conv_bin_to_dec(table[111].max_value, 20, table[111].height, 80.321);
	double x2 = conv.conv_dec_to_bin(table[111].max_value, 20, table[111].height, x1);
	printf("x1 = %ld\nreturn = %f", x1, x2);
	// шаг 4 обработка пакетов, присланных клиентами
	while (1)
	{
		sockaddr_in client_addr;
		int client_addr_size = sizeof(client_addr);
		int bsize = recvfrom(my_sock, &buff[0],
			sizeof(buff), 0,
			(sockaddr*)&client_addr, &client_addr_size);

		if (bsize == SOCKET_ERROR)
			printf("recvfrom() error: %d\n",
				WSAGetLastError());

		BNR pack1;

		memcpy(&pack1, buff, sizeof(pack1));
		printf("recvfrom()%d\n", pack1.value.address);



		if (table[pack1.value.address].name == "слово ИНС")
		{
			DISCRETE pack1;
			memcpy(&pack1, buff, sizeof(pack1));


			SYSTEMTIME st;

			GetLocalTime(&st);

			fprintf(ofile, "\n%-4d-%02d-%02d %02d:%02d:%02d.%-15d",
				st.wYear,
				st.wMonth,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond,
				st.wMilliseconds);

			char* cstr = new char[table[pack1.value.address].name.length() + 1];
			strcpy(cstr, table[pack1.value.address].name.c_str());
			fprintf_s(ofile, "%-35s", cstr);
			fprintf_s(ofile, "%-10.10s", " ");

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "SDI");
			fprintf_s(ofile, "%-35d", pack1.value.sdi);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Подготовка по ЗК");
			fprintf_s(ofile, "%-35d", pack1.value.preparation);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Контроль");
			fprintf_s(ofile, "%-35d", pack1.value.control);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Навигация");
			fprintf_s(ofile, "%-35d", pack1.value.navigation);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Гирокомпассирование");
			fprintf_s(ofile, "%-35d", pack1.value.gyrocompas);

			//fprintf_s(ofile, "\n%-35s", "  ");

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Повторный запуск");
			fprintf_s(ofile, "%-35d", pack1.value.restart);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Шкала подготовки");
			fprintf_s(ofile, "%-35d", pack1.value.scale);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Исправность обогрева");
			fprintf_s(ofile, "%-35d", pack1.value.heating);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Термостатирование");
			fprintf_s(ofile, "%-35d", pack1.value.temp_control);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Нет начальных данных");
			fprintf_s(ofile, "%-35d", pack1.value.init_data);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Нет приема Набс");
			fprintf_s(ofile, "%-35d", pack1.value.no_reception);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Исправность ИНС");
			fprintf_s(ofile, "%-35d", pack1.value.INS);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Готовность ускоренная");
			fprintf_s(ofile, "%-35d", pack1.value.acceleration);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Готовность");
			fprintf_s(ofile, "%-35d", pack1.value.readiness);

			//fprintf_s(ofile, "\n%-35s", "  ");

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "SM");
			fprintf_s(ofile, "%-35d", pack1.value.sm);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "P");
			fprintf_s(ofile, "%-35d\n", pack1.value.p);
		}

		if (table[pack1.value.address].name == "слово СНС")
		{
			FEATURES pack1;
			memcpy(&pack1, buff, sizeof(pack1));


			SYSTEMTIME st;

			GetLocalTime(&st);

			fprintf(ofile, "\n%-4d-%02d-%02d %02d:%02d:%02d.%-15d",
				st.wYear,
				st.wMonth,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond,
				st.wMilliseconds);

			char* cstr = new char[table[pack1.value.address].name.length() + 1];
			strcpy(cstr, table[pack1.value.address].name.c_str());
			fprintf_s(ofile, "%-35s", cstr);
			fprintf_s(ofile, "%-10.10s", " ");

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Запрос начальных данных");
			fprintf_s(ofile, "%-35d", pack1.value.request_data);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Тип рабочей СРНС");
			fprintf_s(ofile, "%-35d", pack1.value.type_srns);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Альманах GPS");
			fprintf_s(ofile, "%-35d", pack1.value.almanach_gps);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Альманах ГЛОНАСС");
			fprintf_s(ofile, "%-35d", pack1.value.almanach_glonass);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Режим работы");
			fprintf_s(ofile, "%-35d", pack1.value.mode);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Подрежимы работы");
			fprintf_s(ofile, "%-35d", pack1.value.submode_srns);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Признак времени");
			fprintf_s(ofile, "%-35d", pack1.value.time_ind);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Диф. режим измерений");
			fprintf_s(ofile, "%-35d", pack1.value.diff_mode);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Отказ изделия");
			fprintf_s(ofile, "%-35d", pack1.value.rejection);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Порог сигнализации");
			fprintf_s(ofile, "%-35d", pack1.value.signal_threshold);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Система координат");
			fprintf_s(ofile, "%-35d", pack1.value.cs);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "SM");
			fprintf_s(ofile, "%-35d", pack1.value.sm);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "P");
			fprintf_s(ofile, "%-35d\n", pack1.value.p);
		}


		if (table[pack1.value.address].name != "слово СНС" && table[pack1.value.address].name != "слово БИНС" && table[pack1.value.address].name != "дата")
		{

			SYSTEMTIME st;

			GetLocalTime(&st);

			fprintf(ofile, "\n%-4d-%02d-%02d %02d:%02d:%02d.%-15d",
				st.wYear,
				st.wMonth,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond,
				st.wMilliseconds);


			char* cstr = new char[table[pack1.value.address].name.length() + 1];
			strcpy(cstr, table[pack1.value.address].name.c_str());
			fprintf_s(ofile, "%-35s", cstr);
			std::cout << pack1.value.high;




			double decvalue = conv.conv_bin_to_dec(table[pack1.value.address].max_value, 20, table[pack1.value.address].height, pack1.value.high);
			fprintf_s(ofile, "%-10.10f", decvalue);


		}



		if (table[pack1.value.address].name == "дата") {

			DATE_ pack1;
			memcpy(&pack1, buff, sizeof(pack1));

			SYSTEMTIME st;

			GetLocalTime(&st);

			fprintf(ofile, "\n%-4d-%02d-%02d %02d:%02d:%02d.%-15d",
				st.wYear,
				st.wMonth,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond,
				st.wMilliseconds);

			char* cstr = new char[table[pack1.value.address].name.length() + 1];
			strcpy(cstr, table[pack1.value.address].name.c_str());
			fprintf_s(ofile, "%-35s", cstr);
			//fprintf_s(ofile, "%-10.10f", pack1.Value);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Год");
			fprintf_s(ofile, "%-35d", pack1.value.y_u);

			fprintf_s(ofile, "\n%-35s", " ");
			fprintf_s(ofile, "%-35s", " ");
			fprintf_s(ofile, "%-35d", pack1.value.y_d);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "Месяц");
			fprintf_s(ofile, "%-35d", pack1.value.m_u);

			fprintf_s(ofile, "\n%-35s", " ");
			fprintf_s(ofile, "%-35s", " ");
			fprintf_s(ofile, "%-35d", pack1.value.m_d);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "День");
			fprintf_s(ofile, "%-35d", pack1.value.d_u);

			fprintf_s(ofile, "\n%-35s", " ");
			fprintf_s(ofile, "%-35s", " ");
			fprintf_s(ofile, "%-35d", pack1.value.d_d);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "SM");
			fprintf_s(ofile, "%-35d", pack1.value.sm);

			fprintf_s(ofile, "\n%-35s", "  ");
			fprintf_s(ofile, "%-35s", "P");
			fprintf_s(ofile, "%-35d\n", pack1.value.p);


		}

	}


}