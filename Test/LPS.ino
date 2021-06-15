// Local Positioning System
float botx = 0;
float boty = 0;
float dir = 0;

bool target = false;
float targetx = 0;
float targety = 0;
float targetoff = 0;

float radius = 0;
float rotspeed = 0;
float axel = 53;

bool pid = false;
float pid_p = 0;
float pid_i = 0;
float pid_d = 0;
float pid_speed = 0;
float prev_error = 0;
float tot_error = 0;


float mspd = 255;



int* LPS_UPDATE(float loop_time, int mspdL, int mspdR) {
  tankangle(mspdL, mspdR);
  float a = (loop_time / 1000) * rotspeed;
  
  if (mspdL != mspdR) {
    float* rtp = rotatep(botx+radius, boty, botx, boty, dir);
    float* nbot = rotatep(botx, boty, rtp[0], rtp[1], a);
    botx = nbot[0];
    boty = nbot[1];
    //dir = (dir + a)%360;  
    dir = fmodf((dir + a), 360);
  
  } else {
    float spd = (loop_time / 1000) * mspdL;
    float* nbot = rotatep(botx, boty+spd, botx, boty, dir);
    botx = nbot[0];
    boty = nbot[1];
  }

  if (target == true) {
    float d = distance(botx, boty, targetx, targety);
    
    if (d <= targetoff) {
      target = false;
      static int result[2]; 
      result[0] = 0;
      result[1] = 0;
      
      return result;  
    }
  }

  int* ctrl = LPS_PID_CTRL(LPS_PID(loop_time), pid_speed);  
  
  return ctrl;
}



void LPS_SET_PID(float p, float i, float d, int spd) {
  pid_p = p;
  pid_i = i;
  pid_d = d;
  pid_speed = spd;
  pid = true;
}

void LPS_PID_OFF() {
  prev_error = 0;
  tot_error = 0;
  pid = false;
}



float LPS_PID(float loop_time) { 
  float error = angle(botx, boty, targetx, targety) - dir;
  float diff = (prev_error - error);
  tot_error = tot_error + error;
  float result = (pid_p * error) + (pid_i * tot_error) + (pid_d * diff);

  return result;  
}



float lspd_to_rad(float lspd, float spd) {
  float u = (axel / 2) * (2 * spd);
  float l = (2 * lspd) - (2 * spd);
  float rad = u / l;
   
  return rad;
}

float rspd_to_rad(float rspd, float spd) {
  float u = (axel / 2) * (2 * spd);
  float l = (2 * spd) - (2 * rspd);
  float rad = u / l;

  return rad;
}



int* LPS_PID_CTRL(float ctrl, float spd) {
  float lspd, rspd;
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

  static int out[2];
  out[0] = lspd;
  out[1] = rspd;
  
  return out;
}



void LPS_TARGET_ON(float x, float y, float error) {
  targetx = x;
  targety = y;
  targetoff = error;
  target = true;
  pid = true;
}

void LPS_TARGET_OFF() {
  target = false;  
}



float LPS_INFO(int index) {
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
    return angle(botx, boty, targetx, targety);
  } else if (index == 6) {
    return (angle(botx, boty, targetx, targety) - dir);
  }
}



float* LPS_CRD() {
  static float crd[3];
  crd[0] = botx;
  crd[1] = boty;
  crd[2] = dir;
  
  return crd;
}



void tankangle(float l, float r) {
  float c, d, t, rl, rr;
  
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



float* rotate(float x, float y, float a) {
  a = a / radian *-1;

  static float crd[2];
  crd[0] = x * cos(a) - y * sin(a);
  crd[1] = x * sin(a) + y * cos(a);
  
  return crd;
  
}



float* rotatep(float x, float y, float mx, float my, float a) {
  float* crd = rotate(x-mx, y-my, a);
  crd[0] = crd[0] + mx;
  crd[1] = crd[1] + my;

  return crd;
}



float distance(float xa, float ya, float xb, float yb) {
  float d = sqrt( sq(xa-xb) + sq(ya-yb ) );
  return d;
}



float angle(float xa, float ya, float xb, float yb) {
  float a;
  if ((xb-xa) != 0) {
    a = atan( (yb-ya) / (xb-xa) ) * radian;
    a = (a-90) * -1;

    if ((xb-xa) < 0) {
      a = a - 180;
    }
    
  } else {
    a = 0;
  }
  return a;
}
