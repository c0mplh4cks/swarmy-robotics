double spd_pid_p = 0;
double spd_pid_i = 0;
double spd_pid_d = 0;

double prev_errorL = 0;
double tot_errorL = 0;
double prev_errorR = 0;
double tot_errorR = 0;
double diffR = 0;
double diffL = 0; 

double spd_cap = 200;
bool spd_pid = true;



void SPD_SET_PID(double p, double i, double d) {
  spd_pid_p = p;
  spd_pid_i = i;
  spd_pid_d = d;
}



void SPD_PID_OFF() {
  tot_errorL = 0;
  tot_errorR = 0;
  diffR = 0;
  diffL = 0;   
  spd_pid = false;
}

void SPD_PID_ON() {
  spd_pid = true;
}


int* SPD_UPDATE(double loop_time, double targetL, double targetR, double spdL, double spdR) {
  double errorL = targetL - (spdL / (loop_time / 1000));
  if (spd_pid) {diffL = errorL - prev_errorL;}
  double errorR = targetR - (spdR / (loop_time / 1000));
  if (spd_pid) {diffR = errorR - prev_errorR;}

  double resultL = (spd_pid_p * errorL) + (spd_pid_i * tot_errorL) + (spd_pid_d * diffL) * spd_pid;
  double resultR = (spd_pid_p * errorR) + (spd_pid_i * tot_errorR) + (spd_pid_d * diffR) * spd_pid;

  if (resultL < spd_cap && resultL > -spd_cap && spd_pid) {
   tot_errorL = tot_errorL + errorL;
  }
  if (resultR < spd_cap && resultR > -spd_cap && spd_pid) {
    tot_errorR = tot_errorR + errorR;   
  } 
  
  prev_errorL = errorL;
  prev_errorR = errorR;

      
  static int spds[2];
  spds[0] = resultL;
  spds[1] = resultR;

  return spds;
}
