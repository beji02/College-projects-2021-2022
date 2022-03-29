#pragma once
#include "domain.h"
#include "DynamicArray.h"

/// <summary>creeaza un nou repository</summary>
/// <returns>un nou obiect de tipul repository</returns>
DynamicArray createRepository(void);

/// <summary>distruge obiectul repository alocat dinamic</summary>
/// <param name="Repository">obiectul de tip repository</param>
void destroyRepository(DynamicArray Repository);

/// <summary>insereaza un nou participant in repository</summary>
/// <param name="Repository">obiectul repository in care se insereaza noul participant</param>
/// <param name="NewParticipant">obiectul nou de tip Participant</param>
void insertParticipant(DynamicArray Repository, Participant NewParticipant);

/// <summary>
/// sterge un participant din repository
/// </summary>
/// <param name="Repository">repositoriul din care se va sterge</param>
/// <param name="participant">participantul care se sterge</param>
void deleteParticipant(DynamicArray Repository, Participant Participant);

/// <summary>cauta un participant in repository</summary>
/// <param name="Repository">repositoriul in care se cauta</param>
/// <param name="Participant">participantul care se cauta</param>
/// <returns>1 daca se afla in repo, 0 altfel</returns>
int searchParticipant(DynamicArray Repository, Participant Participant);

void TestRepository(void);