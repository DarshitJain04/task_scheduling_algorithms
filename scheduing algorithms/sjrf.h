#ifndef SJRF_H
#define SJRF_H
#include "./main.h"

#include <bits/stdc++.h>

using namespace std;

void sjrf_function(vector<Process> processes, int numberOfProcesses)
{
	cout << "\n\t*** Shortest Job Remaining First ***\n";
	int time = 0;
	int executedCount = 0;
	float avgTurnAroundTime = 0;
	float avgWaitTime = 0;
	float avgResponseTime = 0;
	int context_count = 0;
	vector<Process> processInQueue;
	vector<bool> inQueue(numberOfProcesses, false);
	// bool inQueue[numberOfProcesses];
	// fill(inQueue, inQueue+jobCount, false);
	map<int, int> pid_complete;
	while (executedCount != numberOfProcesses)
	{
		for (int i = 0; i < numberOfProcesses; i++)
		{
			if ((processes[i].getArrivalTime() <= time) && (inQueue[i] == false))
			{
				processInQueue.push_back(processes[i]);
				inQueue[i] = true;
			}
		}

		if (processInQueue.size() != 0)
		{
			vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
																processInQueue.end(), compareByBurst);
			(*minPosition).setBurstTime((*minPosition).getBurstTime() - 1);
			time++;
			if ((*minPosition).getBurstTime() == 0)
			{
				pid_complete[(*minPosition).getId()] = time;
				executedCount++;
				processInQueue.erase(minPosition);
			}
		}
		else
		{
			time++;
		}
	}
	for (int i = 0; i < numberOfProcesses; i++)
	{
		processes[i].setCompletionTime(pid_complete[processes[i].getId()]);
		processes[i].setTurnAroundTime(processes[i].getCompletionTime() - processes[i].getArrivalTime());
		processes[i].setWaitingTime(processes[i].getTurnAroundTime() - processes[i].getBurstTime());
		processes[i].setResponseTime(processes[i].getCompletionTime() - processes[i].getBurstTime() - processes[i].getArrivalTime());
		avgWaitTime += processes[i].getWaitingTime();
		avgTurnAroundTime += processes[i].getTurnAroundTime();
		avgResponseTime += processes[i].getResponseTime();
	}
	avgWaitTime = (float)avgWaitTime / numberOfProcesses;
	avgTurnAroundTime = (float)avgTurnAroundTime / numberOfProcesses;
	avgResponseTime = (float)avgResponseTime / numberOfProcesses;
	context_count = processes.size() - 1;
	display(processes, numberOfProcesses, avgWaitTime, avgTurnAroundTime, avgResponseTime, context_count);
}
#endif