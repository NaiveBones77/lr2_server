#pragma once
#include <map>
#include <iostream>

#pragma pack(push,1)
union BNR {
	struct data {
		unsigned address : 8;
		unsigned high : 20;
		unsigned sign : 1;
		unsigned sm : 2;
		unsigned p : 1;
	} value;
};
#pragma pack(pop)

#pragma pack(push,1)
union BCD {
	struct data {
		unsigned address : 8;
		unsigned emp1 : 3;
		unsigned sec : 6;
		unsigned min : 6;
		unsigned hour : 5;
		unsigned emp2 : 1;
		unsigned sm : 2;
		unsigned p : 1;
	} value;
};
#pragma pack(pop)

#pragma pack(push,1)
union DISCRETE {
	struct data {
		unsigned address : 8;
		unsigned sdi : 2;
		unsigned preparation : 1;
		unsigned control : 1;
		unsigned navigation : 1;
		unsigned gyrocompas : 1;
		unsigned emp1 : 1;
		unsigned restart : 1;
		unsigned scale : 3;
		unsigned heating : 1;
		unsigned temp_control : 1;
		unsigned init_data : 1;
		unsigned no_reception : 1;
		unsigned INS : 1;
		unsigned acceleration : 1;
		unsigned readiness : 1;
		unsigned emp2 : 3;
		unsigned sm : 2;
		unsigned p : 1;
	} value;
};
#pragma pack(pop)

#pragma pack(push,1)
union DATE_ {
	struct data {
		unsigned address : 8;
		unsigned emp1 : 2;
		unsigned y_u : 4;
		unsigned y_d : 4;
		unsigned m_u : 4;
		unsigned m_d : 1;
		unsigned d_u : 4;
		unsigned d_d : 1;
		unsigned emp2 : 1;
		unsigned sm : 2;
		unsigned p : 1;
	} value;
};
#pragma pack(pop)

#pragma pack(push,1)
union FEATURES {
	struct data {
		unsigned address : 8;
		unsigned request_data : 1;
		unsigned type_srns : 3;
		unsigned almanach_gps : 1;
		unsigned almanach_glonass : 1;
		unsigned mode : 2;
		unsigned submode_srns : 1;
		unsigned time_ind : 1;
		unsigned emp1 : 2;
		unsigned diff_mode : 1;
		unsigned emp2 : 1;
		unsigned rejection : 1;
		unsigned signal_threshold : 1;
		unsigned cs : 2;
		unsigned emp3 : 3;
		unsigned sm : 2;
		unsigned p : 1;
	} value;
};
#pragma pack(pop)


struct Value {
	std::string name;
	int height;
	double max_value;

};

Value latitude = { "������", 20, 90 };
Value longitude = { "�������", 20, 90 };
Value height = { "������", 19, 19975.3728 };
Value course = { "���� ��������", 16, 90 };
Value pitch = { "������", 16, 90 };
Value roll = { "����", 16, 90 };
Value velocityNS = { "�������� ����� ��", 19, 1053.5822 };
Value velocityEW = { "�������� ������ �����", 19, 1053.5822 };
Value velocity = { "�������� ������������ ������������", 19, 83.2307 };
Value ax = { "��������� ����������", 12, 19.62 };
Value az = { "��������� ����������", 12, 19.62 };
Value ay = { "��������� ����������", 12, 2 };
Value word_state = { "����� ���", 32, 0 };

Value height2 = { "������", 20, 65536 };
Value HDOP = { "HDOP", 15, 512 };
Value VDOP = { "VDOP", 15, 512 };
Value trackangle = { "������� ����", 15, 90 };
Value curlatitude = { "������� ������ ", 20, 90 };
Value curlatitude1 = { "������� ������ (�����)", 11, 0.000085830 };
Value curlongitude = { "������� �������", 20, 90 };
Value curlongitude1 = { "������� ������� (�����) ", 11, 0.000085830 };
Value delay = { "�������� ������", 20, 512 };
Value ut� = { "������� ����� UTC (������� �������)", 6, 32 };
Value ut�1 = { "������� ����� UTC (������� �������)", 20, 512 };
Value Vh = { "������������ ��������", 15, 16384 };
Value dataT = { "����", 32, 0 };
Value word_state1 = { "����� ���", 32, 0 };


std::map <int, struct Value > table = { {200, latitude }, {201, longitude},
								  {241, height},    {204, course},
								  {212, pitch},     {213, roll },
								  {246, velocityNS},{247, velocityEW},
								  {245, velocity }, {217, ax},
								  {218, az},        {219, ay},
								  {62, height2},    {65, HDOP},
								  {66, VDOP},      {67, trackangle},
								  {72, curlatitude},{80, curlatitude1},
								  {73, curlongitude},{81, curlongitude1},
								  {75, delay},     {104, ut�},
								  {96, ut�1},      {117, Vh},
								  {184, word_state},{187, word_state1},
								  {176, dataT} };
