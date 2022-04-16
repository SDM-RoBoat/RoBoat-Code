########################################
# Messages
########################################

# DDControl.msg
float32 left_wheel_vel # Left wheel velocity
float32 right_wheel_vel #right wheen velocity

# infFilterPartials.msg
int32 sender_id # ID of the agent that sent this message
int32[] ids # Array of known IDs
int32[] obs_ids # Array of IDs observed at this time step
std_msgs/Float64MultiArray inf_matrix_prior
std_msgs/Float64MultiArray inf_vector_prior
std_msgs/Float64MultiArray obs_matrix
std_msgs/Float64MultiArray obs_vector

#infFilterResults.msg
int32[] ids # Array of known IDs
std_msgs/Float64MultiArray inf_matrix
std_msgs/Float64MultiArray inf_vector

#PoseMarkers.msg
int32[] ids # Array of known IDs
geometry_msgs/PoseWithCovarianceStamped[] pose_array # Array of 6-dof pose for each tag



