/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix.h>
#include <frc/WPILib.h>

WPI_VictorSPX BallShootFront {1};
WPI_VictorSPX BallShootBack {2};

WPI_TalonSRX Wheel1 {2};
WPI_TalonSRX Wheel2 {4};
WPI_TalonSRX Wheel3 {3};
WPI_TalonSRX Wheel4 {1};

frc::MecanumDrive Mecanums {Wheel4 , Wheel3 , Wheel2 , Wheel1};

frc::Joystick Xbox {0};
frc::Joystick Yoke {1};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

void Robot::RoboControl()
{
  /*########################################################################################################################
      
                Drivetrain Program

  #########################################################################################################################*/
 
  double xboxLX = Xbox.GetRawAxis(0);
  double xboxRX = Xbox.GetRawAxis(4);

  double xboxRY = Xbox.GetRawAxis(5);
  
  if ((xboxRY > -0.1) && (xboxRY < 0.1))
  {
    xboxRY = 0;
  }

  if ((xboxRX > -0.1) && (xboxRX < 0.1))
  {
    xboxRX = 0;
  }

  if ((xboxLX > -0.1) && (xboxLX < 0.1))
  {
    xboxLX = 0;
  }
  
  Mecanums.DriveCartesian(xboxRX , xboxRY , xboxLX);
  
  double speedwheel = (Yoke.GetRawAxis(2) * -1);
  speedwheel = ((speedwheel + 1.0) / 2.0);

  if(Yoke.GetRawButtonPressed(1))
  {
    BallShootFront.Set(speedwheel);
  
    BallShootBack.Set(-speedwheel);
  }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
