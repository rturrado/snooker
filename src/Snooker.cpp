/*
 * Snooker.cpp - a snooker table
 */

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <ctime>
#include <vector>

#include "Ball.hpp"
#include "Color.hpp"
#include "PlayingSurface.hpp"
#include "Pocket.hpp"
#include "Physics.hpp"
#include "Trajectory.hpp"
#include "Utility.hpp"
#include "Vertex.hpp"

using namespace Snooker::Graphics;

// Window size
const int windowWidth  = 500;
const int windowHeight = 500;
// Frames per second
const int framesPerSecond = 25;
const int msBetweenFrames = 1000/framesPerSecond;
// glPerspective parameters
GLdouble fovy  = 60;
GLdouble zNear = 0.1;
GLdouble zFar  = 10000;
// Balls
const int numberOfBalls    = 22;
const int numberOfRedBalls = 15;
const GLdouble ballRadius  = 52.5/2;
// Playing surface
const GLdouble topCushionToBlackSpot      = 324;
const GLdouble topCushionToTopPiramidSpot = psLength/4 - ballRadius*2;
const Color playingSurfaceColor(0.2, 0.8, 0.2);
PlayingSurface playingSurface(playingSurfaceColor);
// Balls' initial positions relative to the playing surface
const Vertex cueBallPosition       (-100, ballRadius, psLength/2-bottomCushionToBaulkLine+100);
const Vertex greenBallPosition (-dRadius, ballRadius, psLength/2-bottomCushionToBaulkLine);
const Vertex brownBallPosition        (0, ballRadius, psLength/2-bottomCushionToBaulkLine);
const Vertex yellowBallPosition (dRadius, ballRadius, psLength/2-bottomCushionToBaulkLine);
const Vertex blueBallPosition         (0, ballRadius, 0);
const Vertex pinkBallPosition         (0, ballRadius, -psLength/4);
const Vertex blackBallPosition        (0, ballRadius, -(psLength/2-topCushionToBlackSpot));
// Vector of red balls' initial positions 
std::vector<const Vertex*> redBallsPositions;
// Ball's colours
const Color cueBallColor    (1.0, 1.0, 1.0); // white
const Color blackBallColor  (0.0, 0.0, 0.0); // black
const Color blueBallColor   (0.0, 0.2, 0.8); // blue
const Color brownBallColor  (0.7, 0.5, 0.1); // brown
const Color greenBallColor  (0.2, 0.6, 0.2); // green
const Color pinkBallColor   (1.0, 0.5, 1.0); // pink
const Color redBallColor    (0.8, 0.2, 0.2); // red 
const Color yellowBallColor (0.9, 0.9, 0.1); // yellow
// Vector of balls
std::vector<BallPtr> balls;
// This enum can be used as an index into the vector of balls
enum Colors { white, black, blue, brown, green, pink, yellow, red };
// Keyboard controls
bool enableRotation    = false;
bool enableTranslation = false;
GLdouble rotationFactor[3]    = { 0.0, 0.0, 0.0 };
GLdouble translationFactor[3] = { 0.0, 0.0, 0.0 };
// Pockets
const int numberOfPockets = 6;
const Vertex bottomLeftPocketPosition (-psWidth/2, 0, psLength/2);
const Vertex bottomRightPocketPosition (psWidth/2, 0, psLength/2);
const Vertex middleLeftPocketPosition (-psWidth/2, 0, 0);
const Vertex middleRightPocketPosition (psWidth/2, 0, 0);
const Vertex topLeftPocketPosition    (-psWidth/2, 0, -psLength/2);
const Vertex topRightPocketPosition    (psWidth/2, 0, -psLength/2);
// Vector of pockets
std::vector<PocketPtr> pockets;
// Threads
boost::thread_group tG;

void drawTable()
{
  // Balls
  for (int i = 0; i < numberOfBalls; i++)
  {
    balls.at(i)->draw();
  }

  // Pockets
  for (int i = 0; i < numberOfPockets; i++)
  {
    pockets.at(i)->draw();
  }

  // Playing surface
  playingSurface.draw();
}

void display()
{
  // Fill the background in black
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Clear modelview
  glLoadIdentity();
  glRotated(rotationFactor[0], 1, 0, 0);
  glRotated(rotationFactor[1], 0, 1, 0);
  glRotated(rotationFactor[2], 0, 0, 1);
  glTranslated(translationFactor[0], translationFactor[1], translationFactor[2]);
  drawTable();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
  static unsigned int axis = 0;

  switch (key)
  {
    case 27:  exit(1);
              break;
    case 'r': enableRotation    = true;
              enableTranslation = false;
              break;
    case 't': enableRotation    = false;
              enableTranslation = true;
              break;
    case 'x': axis = 0;
              break;
    case 'y': axis = 1;
              break;
    case 'z': axis = 2;
              break;
    case '+': if (enableRotation)
              {
                rotationFactor[axis] += 1;
              }
              if (enableTranslation)
              {
                translationFactor[axis] += 50;
              }
              break;
    case '-': if (enableRotation)
              {
                rotationFactor[axis] -= 1;
              }
              if (enableTranslation)
              {
                translationFactor[axis] -= 50;
              }
              break;
    default:  break;
  }
}

void timer(int value)
{
  if (value)
  {
    glutPostRedisplay();
  }
  glutTimerFunc(msBetweenFrames, timer, value);
}

void visibility(int state)
{
  switch (state)
  {
    case GLUT_VISIBLE:     timer(1);
                           break;
    case GLUT_NOT_VISIBLE: timer(0);
                           break;
    default:               break;
  }
}

void initRedBallsPositions()
{
  GLdouble xCoord = 0;
  GLdouble zCoord = -(psLength/2-topCushionToTopPiramidSpot);
  GLdouble xCoordFirstBallThisRow;
  GLdouble xDeltaNextRow = ballRadius*2 * cos(60*pi/180);
  GLdouble zDeltaNextRow = ballRadius*2 * sin(60*pi/180);
  GLdouble xDeltaThisRow = ballRadius*2;

  for (int row = 1; row <= 5; row++)
  {
    xCoordFirstBallThisRow = xCoord;
    for (int i = 1; i <= row; i++)
    {
      redBallsPositions.push_back(new Vertex(xCoord, ballRadius, zCoord));
      xCoord -= xDeltaThisRow;
    }
    xCoord = xCoordFirstBallThisRow + xDeltaNextRow;
    zCoord -= zDeltaNextRow;
  }
}

void initBalls()
{
  balls.push_back (BallPtr (new Ball (ballRadius, cueBallPosition,    cueBallColor    )));
  balls.push_back (BallPtr (new Ball (ballRadius, blackBallPosition,  blackBallColor  )));
  balls.push_back (BallPtr (new Ball (ballRadius, blueBallPosition,   blueBallColor   )));
  balls.push_back (BallPtr (new Ball (ballRadius, brownBallPosition,  brownBallColor  )));
  balls.push_back (BallPtr (new Ball (ballRadius, greenBallPosition,  greenBallColor  )));
  balls.push_back (BallPtr (new Ball (ballRadius, pinkBallPosition,   pinkBallColor   )));
  balls.push_back (BallPtr (new Ball (ballRadius, yellowBallPosition, yellowBallColor )));
  for (int i = 0; i < numberOfRedBalls; i++)
  {
    balls.push_back (BallPtr (new Ball (ballRadius, *redBallsPositions[i], redBallColor )));
  }
}

void initPockets()
{
  pockets.push_back (PocketPtr (new Pocket(bottomLeftPocketPosition  )));
  pockets.push_back (PocketPtr (new Pocket(bottomRightPocketPosition )));
  pockets.push_back (PocketPtr (new Pocket(middleLeftPocketPosition  )));
  pockets.push_back (PocketPtr (new Pocket(middleRightPocketPosition )));
  pockets.push_back (PocketPtr (new Pocket(topLeftPocketPosition     )));
  pockets.push_back (PocketPtr (new Pocket(topRightPocketPosition    )));
}

void initGraphics(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("Snooker");

  initRedBallsPositions();
  initBalls();
  initPockets();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(msBetweenFrames, timer, 1);
  glutVisibilityFunc(visibility);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, ((GLdouble) windowWidth) / windowHeight, zNear, zFar);
  gluLookAt(0, 1000, 2000, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
}

void moveBallCircularNoFriction(unsigned int index)
{
  BallPtr bp = balls.at(index);

  GLdouble aRadius = 300;
  const Vertex& oldPosition = bp->getPosition();
  GLdouble oldX = oldPosition.getX();
  GLdouble oldY = oldPosition.getY();
  GLdouble oldZ = oldPosition.getZ();
  GLdouble newX;
  GLdouble newZ;
  
  for (int angle = 0; ; angle = ((angle+1) % 360))
  {
    newX = oldX - aRadius + aRadius * cos(angle*pi/180);
    newZ = oldZ + aRadius * sin(angle*pi/180);
    bp->move(Vertex(newX, oldY, newZ));
    boost::this_thread::sleep(boost::posix_time::milliseconds(msBetweenFrames));
  }
}

void moveBallLinearFriction(unsigned int index)
{
  float angle = 100;
  float springDistance = 0.1;

  BallPtr ballPtr = balls.at(index);
  Vertex vertex   = ballPtr->getPosition();
  Trajectory trajectory(vertex, angle);
  
  time_t startTime, currentTime;
  float timeIncr;
  time(&startTime);
  while (ballPtr->move(trajectory, springDistance, timeIncr))
  {
    boost::this_thread::sleep(boost::posix_time::milliseconds(msBetweenFrames));
    time(&currentTime);
    timeIncr = static_cast<float>(difftime(currentTime, startTime));
  }
}

void playMain()
{
  std::cout << "Let's play!" << std::endl;
  // Move cue ball in a linear trajectory
  tG.create_thread(boost::bind(moveBallLinearFriction, white));
  // Move blue ball in a circular trajectory
  tG.create_thread(boost::bind(moveBallCircularNoFriction, blue));
  std::cout << "Did you see the balls moving?" << std::endl;
}

int main(int argc, char **argv)
{
  initGraphics(argc, argv);
  tG.create_thread(boost::bind(playMain));
  glutMainLoop();

  tG.join_all();
  return 0;
}
