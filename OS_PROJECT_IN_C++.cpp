#include <iostream>
#include <Windows.h>
#include<iomanip>
using namespace std;

struct processes
{
    int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, priority = 0;
} * process;

int total_time = 0, processes_count, queue_count;

int next_process_to_execute()
{
    int high_priority = 0, less_burst_time = 0, process_index = 0;

    for (int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 &&total_time > process[index].arrival &&process[index].waiting >= 10)
        {
            process[index].priority = process[index].waiting / 10;		//assigning priority by using the formula
        }
    }

    for (int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 && (process[index].priority > high_priority))
        {
            high_priority = process[index].priority;
            break;
        }
    }

    for (int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (process[index].priority > high_priority))
        {
            high_priority = process[index].priority;
        }
    }

    for (int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 &&
            (total_time >= process[index].arrival) &&
            (process[index].priority == high_priority))
        {
            less_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (int index = 0; index < processes_count; index++)
    {
        if ((less_burst_time > process[index].burst) &&
            (process[index].burst > 0) &&
            (total_time >= process[index].arrival) &&
            (process[index].priority == high_priority))
        {
            less_burst_time = process[index].burst;
            process_index = index;
        }
    }
    return process_index;
}

bool all_processes_completed()
{
    for (int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool all_arrived_processes_completed()
{
    for (int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 && total_time >= process[index].arrival)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void execute_processes()
{
    while (!all_processes_completed())
    {
        if (!all_arrived_processes_completed())
        {
            int process_id = next_process_to_execute();

            cout << "\nPROCESS " << process_id << " E  X  E  C  U  T  I  N  G  . . . . . .  ";

            while (process[process_id].burst > 0)
            {
                ++total_time;
                --process[process_id].burst;
                Sleep(50);
                for (int index = 0; index < processes_count; index++)
                {
                    if (index != process_id && total_time > process[index].arrival && process[index].burst > 0)
                    {
                        ++process[index].waiting;
                    }
                }
            }

            process[process_id].completion = total_time;
            process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
            cout << "\n\n\nPROCESS "
                 << process_id
                 << " EXECUTED.\n";
        }
        else
        {
            ++total_time;
        }
    }
}

void display_table()
{
    cout << "\n\nPROCESS     :  ARRIVAL\t BURST\t COMP\t TURN\t WAITING\t\n";
    cout << "__________________________________________________________________\n";

    for (int index = 0; index < processes_count; index++)
    {
        cout << "PROCESS "
             << index << "   :  "
             << process[index].arrival << "\t "
             << process[index].burst_backup
             << "\t " << process[index].completion
             << "\t " << process[index].turn_around << "\t " << process[index].waiting << "\n\n";
    }

    cout << "__________________________________________________________________\n";

    float total_turnaround_time = 0, total_waiting_time = 0;

    for (int index = 0; index < processes_count; index++)
    {
        total_turnaround_time += process[index].turn_around;
    }
    total_turnaround_time /= processes_count;

    for (int index = 0; index < processes_count; index++)
    {
        total_waiting_time += process[index].waiting;
    }
    total_waiting_time /= processes_count;

    cout << "\n\tAVERAGE TURN_-AROUND TIME : " << total_turnaround_time << "\n";
    cout << "\n\tAVERAGE WAITING TIME : " << total_waiting_time << "\n\n\n";
}

int main()
{	
	cout<<"\t\tOPERATING SYSTEM PROJECT ON SCHEDULING WITH AGING AND SJF\n\n";
    cout << "Enter Number of processes : ";
    cin >> processes_count;
    process = new processes[processes_count];
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\nINPUT FORMAT SHOULD BE => Arrival_Time      Burst_timeT\n\n\n";
    cout<<setw(40)<<"ARRIVAL TIME"<<setw(20)<<"BURST TIME";

    for (int index = 0; index < processes_count; index++)
    {
        cout << "\nProcess ID" << index << " DETAILS : ";
        cin >> process[index].arrival >> process[index].burst;
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    cout << "EXECUTION STARTED..... : \n";
    execute_processes();
    cout << "\n\nALL PROCESS HAVE BEEN EXECUTRD\n\n";
    system("pause");
    system("cls");
    display_table();
    system("pause");
}
