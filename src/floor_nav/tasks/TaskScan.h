#ifndef TASK_SCAN_H
#define TASK_SCAN_H

#include "task_manager_lib/TaskInstance.h"
#include "floor_nav/SimTasksEnv.h"

using namespace task_manager_lib;

namespace floor_nav {
    struct TaskScanConfig : public TaskConfig {
        TaskScanConfig() {
            define("angle",  2*M_PI,"Total angle to rotate",false, angle);
            define("angular_velocity",  0.5,"Rotation speed, its sign gives the direction",false, angular_velocity);
        }

        // convenience aliases, updated by update from the config data
        double angle;
        double angular_velocity;
    };

    class TaskScan : public TaskInstance<TaskScanConfig,SimTasksEnv>
    {
        protected:
            double last_heading;
            double rotated;
        public:
            TaskScan(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskScan() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryScan : public TaskDefinition<TaskScanConfig, SimTasksEnv, TaskScan>
    {

        public:
            TaskFactoryScan(TaskEnvironmentPtr env) : 
                Parent("Scan","Rotate on the spot to scan the surroundings",true,env) {}
            virtual ~TaskFactoryScan() {};
    };
};

#endif // TASK_SCAN_H
