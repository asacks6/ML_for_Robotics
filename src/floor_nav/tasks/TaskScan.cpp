#include <math.h>
#include "TaskScan.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;

TaskIndicator TaskScan::initialise() 
{
    RCLCPP_INFO(getNode()->get_logger(),"Scanning over %.0f deg", cfg->angle*180./M_PI);
    last_heading = env->getPose2D().theta;
    rotated = 0.0;
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskScan::iterate()
{
    // Se acumula el giro entre iteraciones porque el angulo absoluto da la vuelta en +-pi
    double heading = env->getPose2D().theta;
    rotated += fabs(remainder(heading - last_heading,2*M_PI));
    last_heading = heading;
    if (rotated >= cfg->angle) {
		return TaskStatus::TASK_COMPLETED;
    }
    env->publishVelocity(0.0, cfg->angular_velocity);
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskScan::terminate()
{
    env->publishVelocity(0,0);
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryScan);
