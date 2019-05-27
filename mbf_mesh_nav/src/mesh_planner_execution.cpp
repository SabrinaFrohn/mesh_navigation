/*
 *  Copyright 2019, Sebastian Pütz
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  authors:
 *    Sebastian Pütz <spuetz@uni-osnabrueck.de>
 *
 */
#include "mbf_mesh_nav/mesh_planner_execution.h"

namespace mbf_mesh_nav
{

MeshPlannerExecution::MeshPlannerExecution(
    const std::string name,
    const mbf_mesh_core::MeshPlanner::Ptr &planner_ptr,
    const MeshPtr &mesh_ptr,
    const MoveBaseFlexConfig &config,
    boost::function<void()> setup_fn,
    boost::function<void()> cleanup_fn)
      : AbstractPlannerExecution(name, planner_ptr, toAbstract(config), setup_fn, cleanup_fn),
        mesh_ptr_(mesh_ptr)
{
  ros::NodeHandle private_nh("~");
  private_nh.param("planner_lock_mesh", lock_mesh_, true);
}

MeshPlannerExecution::~MeshPlannerExecution()
{
}

mbf_abstract_nav::MoveBaseFlexConfig MeshPlannerExecution::toAbstract(const MoveBaseFlexConfig &config)
{
  // copy the planner-related abstract configuration common to all MBF-based navigation
  mbf_abstract_nav::MoveBaseFlexConfig abstract_config;
  abstract_config.planner_frequency = config.planner_frequency;
  abstract_config.planner_patience = config.planner_patience;
  abstract_config.planner_max_retries = config.planner_max_retries;
  return abstract_config;
}

uint32_t MeshPlannerExecution::makePlan(const geometry_msgs::PoseStamped& start,
                                           const geometry_msgs::PoseStamped& goal,
                                           double tolerance,
                                           std::vector<geometry_msgs::PoseStamped> &plan,
                                           double &cost,
                                           std::string &message)
{
  if (lock_mesh_)
  {
    // TODO
    //boost::unique_lock<mesh_map::MeshMap::mutex_t> lock(*(mesh_ptr_->getMutex()));
    //return planner_->makePlan(start, goal, tolerance, plan, cost, message);
  }
  return planner_->makePlan(start, goal, tolerance, plan, cost, message);
}

} /* namespace mbf_mesh_nav */
