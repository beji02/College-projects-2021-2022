#pragma once


typedef struct {
	char* Nume;
	char* Prenume;
	int Scor;
}__Participant, *Participant;


/// <summary>
/// verifica daca doua obiecte de tip Participant sunt egale	
/// </summary>
/// <param name="p1">
///	primul obiect de tip Participant
/// </param>
/// <param name="p2">
/// al doilea obiect de tip Participant
/// </param>
/// <returns>
/// 1 daca cele doua sunt egale
/// 0 altfel
/// </returns>
int IsEqual(Participant p1, Participant p2);

/// <summary>
/// creeaza un obiect de tip Participant
/// </summary>
/// <param name="Nume">
/// numele participantului
/// </param>
/// <param name="Prenume">
/// prenumele participantului
/// </param>
/// <param name="Scor">
/// scorul participantului
/// </param>
/// <returns>
/// un nou obiect de tipul Participant
/// </returns>
Participant CreateParticipant(char* Nume, char* Prenume, int Scor);

/// <summary>
/// distruge un obiect de tip Participant
/// </summary>
/// <param name="Part">
/// obiectul care va fi distrus
/// </param>
void DestroyParticipant(Participant Part);

void TestDomain(void);