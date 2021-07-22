// Local Positioning System
double botx = 0;
double boty = 0;
double dir = 0;
double angleoff = 5;

bool target = false;
double targetx = 0;
double targety = 0;
double targetoff = 0;

double radius = 0;
double rotspeed = 0;
double axel = 7.5;

bool pid = false;
double pid_p = 0;
double pid_i = 0;
double pid_d = 0;
double pid_speed = 0;
double prev_error = 0;
double tot_error = 0;

double mspd = 255;



double* LPS_UPDATE(double loop_time, double mspdL, double mspdR) {
  tankangle(mspdL, mspdR);
  double a = rotspeed;
  
  if (mspdL != mspdR) {
    double* rtp = rotatep(botx+radius, boty, botx, boty, dir);
    double* nbot = rotatep(botx, boty, rtp[0], rtp[1], a);
    botx = nbot[0];
    boty = nbot[1];
    dir = dir + a;
    if (dir >= 180) {dir = dir-360;}
    if (dir < -180) {dir = dir+360;} 
  
  } else {
    double dst = mspdL;
    double* nbot = rotatep(botx, boty+dst, botx, boty, dir);
    botx = nbot[0];
    boty = nbot[1];
  }

  if (target == true) {
    double spd_brake;
    double d = distance(botx, boty, targetx, targety);
    double ta = angle(botx, boty, targetx, targety, 0);
    
    if (pid_speed != 0) {
      double spd_brake = d / abs(pid_speed);
      double pwm_brake = BRAKE_TIME(loop_time);
      if (spd_brake < pwm_brake) {
        pid_speed = 5 * (abs(pid_speed)/pid_speed);
      }
    }
    
    if ((d <= targetoff) || ((abs(ta-dir) < angleoff) && (pid_speed == 0))) {
      target = false;
      static double result[2]; 
      result[0] = 0;
      result[1] = 0;
      
      return result;  
    }
  }

  double* ctrl = LPS_PID_CTRL(LPS_PID(loop_time, pid_speed), pid_speed); 
  
  return ctrl;
}



void LPS_SET_PID(double p, double i, double d, int spd) {
  pid_p = p;
  pid_i = i;
  pid_d = d;
  pid_speed = spd;
}

void LPS_PID_OFF() {
  prev_error = 0;
  tot_error = 0;
  pid = false;
}

void LPS_PID_ON() {
  pid = true;
}



double LPS_PID(double loop_time, double spd) { 
  double cdir = dir;
  if (spd < 0) {
    cdir = dir + 180;
  }
  
  double error = angle(botx, boty, targetx, targety, cdir); 
  double diff = (error - prev_error);
  if (pid) {tot_error = tot_error + error;}
  if (abs(error) < angleoff) {tot_error = 0;}
  double result = ((pid_p * error) + (pid_i * tot_error) + (pid_d * diff)) * pid;
  if (pid) {prev_error = error;}

  return result;  
}



double lspd_to_rad(double lspd, double spd) {
  double u = (axel / 2) * (2 * spd);
  double l = (2 * lspd) - (2 * spd);
  double rad = u / l;
   
  return rad;
}

double rspd_to_rad(double rspd, double spd) {
  double u = (axel / 2) * (2 * spd);
  double l = (2 * spd) - (2 * rspd);
  double rad = u / l;

  return rad;
}



double* LPS_PID_CTRL(double ctrl, double spd) {
  double lspd, rspd;
  rspd = spd - 0.5 * ctrl;
  lspd = ctrl + rspd;

  if (rspd > mspd) {
    rspd = mspd;
  } else if (rspd < -mspd) {
    rspd = -mspd;
  }

  if (lspd > mspd) {
    lspd = mspd;
  } else if (lspd < -mspd) {
    lspd = -mspd;
  }

  static double out[2];
  out[0] = lspd;
  out[1] = rspd;
  
  return out;
}



void LPS_TARGET_ON(double x, double y, double error) {
  targetx = x;
  targety = y;
  targetoff = error;
  target = true;
}

void LPS_TARGET_OFF() {
  target = false;  
}



double LPS_INFO(int index) {
  if (index == 0) {
    return pid;
  } else if (index == 1) {
    return target;
  } else if (index == 2) {
    return rotspeed;
  } else if (index == 3) {
    return radius;
  } else if (index == 4) {
    return distance(botx, boty, targetx, targety);
  } else if (index == 5) {
    return angle(botx, boty, targetx, targety, dir);
  } else if (index == 6) {
    return (angle(botx, boty, targetx, targety, dir));
  }
}



double* LPS_CRD() {
  static double crd[3];
  crd[0] = botx;
  crd[1] = boty;
  crd[2] = dir;
  
  return crd;
}



void tankangle(double l, double r) {
  double c, d, t, rl, rr;
  
  if (l == r) {
    radius = 0;
    rotspeed = 0;
    return;
    
  } else if (l == 0) {
    radius = -(axel / 2);
    c = -axel * 2 * PI;
    rotspeed = r/c * 360;
    
  } else if (r == 0) {
    radius = axel / 2;
    c = axel * 2 * PI;
    rotspeed = l/c * 360;
    
  } else {
    rr = 1 / ( ( (l/r) - 1 ) / axel );
    rl = rr + axel;
    radius = (rr + rl) / 2;
    c = rr * 2 * PI;
    rotspeed = r/c * 360;
  }
}



double* rotate(double x, double y, double a) {
  a = a / radian *-1;

  static double crd[2];
  crd[0] = x * cos(a) - y * sin(a);
  crd[1] = x * sin(a) + y * cos(a);
  
  return crd;
  
}



double* rotatep(double x, double y, double mx, double my, double a) {
  double* crd = rotate(x-mx, y-my, a);
  crd[0] = crd[0] + mx;
  crd[1] = crd[1] + my;

  return crd;
}



double distance(double xa, double ya, double xb, double yb) {
  double d = sqrt( sq(xa-xb) + sq(ya-yb ) );
  return d;
}



double angle(double xa, double ya, double xb, double yb, double dir) {
  double a;

  double dx = (xb - xa);
  double dy = (yb - ya);

  if (dx == 0) {
    if (yb < ya) {
      a = dir - 180;
    } else {
      a = dir;
    }
  
  } else {
    double r = (dy / dx);
    a = atan(r)*radian - (90 - dir);
  
    if (xb < xa) {
      a = a + 180;
    }
    if (a > 180) {
      a = a - 360;
    }
  }

  a = fmodf((a*-1 + 180), 360) - 180;
  return a;    
}
