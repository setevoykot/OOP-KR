#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <crtdbg.h>  
#include "stdafx.h"

class dekanat {		//����� �������
public:
	dekanat() {		//����������� �� ���������
		strcpy(dekan, "");
	};

	~dekanat() {		//����������
		strcpy(dekan, "");
	};

	void set_dekan(void) {	//��������� ��������
		gets_s(dekan);
	};

	char *get_dek(void) { return dekan; };
private:
	char dekan[25];
};

class kafedra : public dekanat {			//����� �������
public:
	kafedra() {			//����������� �� ���������
		strcpy(nazv, "");
	};
	~kafedra() {			//���������
		strcpy(nazv, "");
	};

	void set_kaf(void) {	//��������� ��������
		gets_s(nazv);
	};

	char *get_nazv(void) { return nazv; };
protected:
	char nazv[25];
};

class gruppa : public kafedra {		//����� ������
public:
	gruppa() {			//����������� �� ���������
		strcpy(nomer, "");
	};

	~gruppa() {			//����������
		strcpy(nomer, "");
	};

	void set_nomer(void) {	//��������� ��������
		gets_s(nomer);
	};

	char *get_nomer(void) { return nomer; };
protected:
	char nomer[25];
};

class student : public gruppa {		//����� �������
public:
	void set_fio(void) {	//��������� ��������
		gets_s(fio);
	};

	void set_uchgod(void) {	//��������� ��������
		scanf("%d", &uchgod);
	};

	void set_sem1(void) {	//��������� ��������
		scanf("%d", &sem1);
	};

	void set_sem2(void) {	//��������� ��������
		scanf("%d", &sem2);
	};

	char *get_fio(void) { return fio; };
	int get_uchgod(void) { return uchgod; };
	int get_sem1(void) { return sem1; };
	int get_sem2(void) { return sem2; };

protected:
	char fio[25];
	int uchgod;
	int sem1, sem2;
};

class service : public student {		//����� ������
public:
	service()					//����������� �� ���������
	{
		f_dek = "c:\\BD_Dekanata.dat";		//����� ������
		f_dek_k = "c:\\BD_Dekanata_k.dat";
	}


	void dobavlenie(void) {
		FILE *f;
		student stud;

		f = fopen(f_dek, "a+b");				//�������� �����

		int i, j;

		printf("\tVvedite dannye studenta:\n");
		fflush(stdin);
		printf("F.I.O. dekana: ");		stud.set_dekan();
		fflush(stdin);
		printf("Nazvanie kafedry: ");	stud.set_kaf();
		fflush(stdin);
		printf("N gruppy: ");			stud.set_nomer();

		fflush(stdin);
		printf("F.I.O. studenta: ");	stud.set_fio();
		fflush(stdin);

		printf("Vvedite kol-vo uchebnyh let: ");	scanf("%d", &j);

		for (i = 0; i < j; i++)
		{
			printf("Uchebnyj god: ");		stud.set_uchgod();
			printf("Itogovaja ocenka za 1 semestr: ");		stud.set_sem1();
			printf("Itogovaja ocenka za 2 semestr: ");		stud.set_sem2();

			fwrite(&stud, sizeof(student), 1, f);	//������ � ����
		}

		fclose(f);								//�������� �����
	}

	void udalenie(void) {
		FILE *f, *fk;
		student stud;
		char fio[25];
		int fl = 0;

		fflush(stdin);
		printf("Vvedite F.I.O. udaljaemogo studenta: "); gets_s(fio);

		f = fopen(f_dek, "r+b");			//�������� ����� ��� ������
		fk = fopen(f_dek_k, "w+b");			//�������� � �������� ���������� �����

		while (fread(&stud, sizeof(student), 1, f) != NULL)		//������ ������
			if (strcmp(stud.get_fio(), fio) != 0)
				fwrite(&stud, sizeof(student), 1, fk);
			else
				fl = 1;

		fclose(f);
		fclose(fk);

		if (fl == 1)
		{
			f = fopen(f_dek, "w+b");
			fk = fopen(f_dek_k, "r+b");

			while (fread(&stud, sizeof(student), 1, fk) != NULL)
				fwrite(&stud, sizeof(student), 1, f);

			fclose(f);
			fclose(fk);

			printf("Dannye studenta udaleny.\n");
		}
		else
			printf("Dannye ne najdeny.\n");

		remove(f_dek_k);		//�������� ���������� �����
		_getch();

	}

	void shapka(void) {
		printf("   Fakulnet         Dekan        Gruppa     F.I.O. stud  Uch god  1 sem. 2 sem.\n");

	}

	void stroka(student stud, student stud_pred) {

		if (strcmp(stud.get_fio(), stud_pred.get_fio()) != 0)
			printf("%-15s %-15s %-10s %-15s %4d   %4d   %4d\n",
				stud.get_nazv(), stud.get_dek(), stud.get_nomer(), stud.get_fio(), stud.get_uchgod(), stud.get_sem1(), stud.get_sem2());
		else
			printf("                                                           %4d   %4d   %4d\n",
				stud.get_uchgod(), stud.get_sem1(), stud.get_sem2());

	}


	void poisk(void) {
		FILE *f;
		student stud, stud_pred;

		char fio[25];
		int fl = 0;

		fflush(stdin);
		printf("Vvedite F.I.O. studenta: "); gets_s(fio);

		f = fopen(f_dek, "r+b");

		while (fread(&stud, sizeof(student), 1, f) != NULL)
			if (strcmp(stud.get_fio(), fio) == 0)
			{
				if (fl == 0) shapka();
				stroka(stud, stud_pred);
				fl = 1;
				stud_pred = stud;
			}

		fclose(f);

		if (fl == 0)
			printf("Dannye ne najdeny.\n");

		getch();
	}

	void demonstracija(void) {
		FILE *f;
		student stud, stud_pred;

		f = fopen(f_dek, "r+b");

		shapka();

		while (fread(&stud, sizeof(student), 1, f) != NULL) {
			stroka(stud, stud_pred);
			stud_pred = stud;
		}

		fclose(f);
		getch();
	}

protected:
	char *f_dek;		//��������� �� ����� ����� � �������
	char *f_dek_k;		//��������� �� ����� ���������� �����
};


void main(void)
{
	service serv;

	int m = 1;		//��������������� ����������

	while (m < 5)
	{
		system("cls");		//������� ������
		printf("\t\tVyberite deistvie i vvedite nomer:\n");
		printf("\t1. Dobavit' novuju zapis'\n");
		printf("\t2. Udalit' zapis'\n");
		printf("\t3. Poisk zapisi\n");
		printf("\t4. Prosmotr zapisej\n");
		printf("\t5. Vyhod\n");
		printf(">> ");

		scanf("%d", &m);	//������ ������ ����

		switch (m)
		{
		case 1: serv.dobavlenie(); break;
		case 2: serv.udalenie(); break;
		case 3: serv.poisk(); break;
		case 4: serv.demonstracija(); break;
		default: break;
		}
	}

	printf("\nPress any key to continue ...\n");
	getch();
}

