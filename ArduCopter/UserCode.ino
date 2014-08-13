// agmatthews USERHOOKS

void userhook_init()
{
    // put your initialisation code here
    
  armpwm1 = 1500;
  armpwm2 = 1500;
  armpwm3 = 1500;
  APM_RC.enable_out(4);
  APM_RC.enable_out(5);
  APM_RC.enable_out(6);
  APM_RC.OutputCh(4,armpwm1);
  APM_RC.OutputCh(5,armpwm2);
  APM_RC.OutputCh(6,armpwm3);
}

void userhook_MediumLoop()
{
    // put your 50Hz code here
    //use pwm1,2,3 for setting the pwm values
    APM_RC.OutputCh(4,armpwm1);
    APM_RC.OutputCh(5,armpwm2);
    APM_RC.OutputCh(6,armpwm3);
}
