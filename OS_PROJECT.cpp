#include <iostream>
#include <Windows.h>

using namespace std;

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, wait = 0, response = 0, priority = 0;
} * process;

short int total_time = 0, processes_count, queue_count;

int process_execution()
{
    int max_priority = 0, less_burst_time = 0, process_index = 0;

    for (short int i = 0; i < processes_count; i++)
    {
        if (process[i].burst > 0 &&
            total_time > process[i].arrival &&
            process[i].wait >= 10)
        {
            process[i].priority = process[i].wait / 10;
        }
    }

    for (short int i = 0; i < processes_count; i++)
    {
        if ((process[i].burst) > 0 && (process[i].priority > max_priority))
        {
            max_priority = process[i].priority;
            break;
        }
    }

    for (short int i = 0; i < processes_count; i++)
    {
        if ((process[i].burst > 0) && (process[i].priority > max_priority))
        {
            max_priority = process[i].priority;
        }
    }

    for (short int i = 0; i < processes_count; i++)
    {
        if ((process[i].burst) > 0 &&
            (total_time >= process[i].arrival) &&
            (process[i].priority == max_priority))
        {
            less_burst_time = process[i].burst;
            process_index = i;
            break;
        }
    }

    for (short int i = 0; i < processes_count; i++)
    {
        if ((less_burst_time > process[i].burst) &&
            (process[i].burst > 0) &&
            (total_time >= process[i].arrival) &&
            (process[i].priority == max_priority))
        {
            less_burst_time = process[i].burst;
            process_index = i;
        }
    }
    return process_index;
}

bool process_state()
{
    for (short int i = 0; i < processes_count; i++)
    {
        if (process[i].burst > 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool process_arrived()
{
    for (short int i = 0; i < processes_count; i++)
    {
        if (process[i].burst > 0 && total_time >= process[i].arrival)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void main_process()
{
    while (!process_state())
    {
        if (!process_arrived())
        {
            int process_id = process_execution();

            cout << "\nProcess under execution is => " << process_id;

            while (process[process_id].burst > 0)
            {
                ++total_time;
                --process[process_id].burst;
                Sleep(50);
                for (short int index = 0; index < processes_count; index++)
                {
                    if (index != process_id && total_time > process[index].arrival && process[index].burst > 0)
                    {
                        ++process[index].wait;
                    }
                }
            }

            process[process_id].completion = total_time;
            process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
            cout << "\nProcess number "<< process_id<< " has been executed.\n";
        }
        else
        {
            ++total_time;
        }
    }
}

void table_maker()
{
    cout << "\n\nPROCESS    ||  ARRIVAL\t BURST\t COMP\t TURN\t wait\t\n";
    cout << "--------------------------------------------------------------------------\n";

    for (short int index = 0; index < processes_count; index++)
    {
        cout << "Process "<< index << "   |  "<< process[index].arrival << "\t "<< process[index].burst_backup<< "\t " << process[index].completion<< "\t " << process[index].turn_around << "\t " << process[index].wait << "\n\n";
    }

    cout << "--------------------------------------------------------------------------\n";

    float total_turnaround_time = 0, total_wait_time = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        total_turnaround_time += process[index].turn_around;
    }
    total_turnaround_time /= processes_count;

    for (short int index = 0; index < processes_count; index++)
    {
        total_wait_time += process[index].wait;
    }
    total_wait_time /= processes_count;

    cout << "\nAverage Turn around Time | " << total_turnaround_time << "\n";
    cout << "\nAverage wait Time | " << total_wait_time << "\n\n\n";
}

int main()
{
    cout << "Enter Processes Count : ";
    cin >> processes_count;
    process = new processes[processes_count];
    cout << "\nEnter Foramt AT BT\n";

    for (short int index = 0; index < processes_count; index++)
    {
        cout << "\nP " << index << " details : ";
        cin >> process[index].arrival >> process[index].burst;
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    cout << "Execution Started : \n";
    main_process();
    cout << "\n\nAll Processes executed\n\n";
    table_maker();
    system("pause");
}
