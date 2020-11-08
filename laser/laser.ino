byte faceColors[6] = {0, 0, 0, 0, 0, 0};
enum types {basic, laserR, laserG, laserB, mirror, split2, split3, splitAll};
byte type = basic;
enum functions {start, laser, interact};
byte function = start;

void setup() {
  // put your setup code here, to run once:
  
}

void setFaceOnClick()
{
  FOREACH_FACE(f) {
    faceColors[f] = 0;
  }
  switch (type)
  {
    case basic:
      {
        setColor(OFF);
        break;
      }
    case laserR:
      {
        setColor(OFF);
        setColorOnFace(RED, 0);
        faceColors[0] = 1;
        break;
      }
    case laserG:
      {
        setColor(OFF);
        setColorOnFace(GREEN, 0);
        faceColors[0] = 2;
        break;
      }
    case laserB:
      {
        setColor(OFF);
        setColorOnFace(BLUE, 0);
        faceColors[0] = 3;
        break;
      }
    case mirror:
      {
        setColor(OFF);
        setColorOnFace(WHITE, 0);
        setColorOnFace(WHITE, 1);
        setColorOnFace(WHITE, 2);
        break;
      }
    case split2:
      {
        setColor(OFF);
        setColorOnFace(CYAN, 0);
        setColorOnFace(CYAN, 2);
        setColorOnFace(CYAN, 4);
        break;
      }
    case split3:
      {
        setColor(OFF);
        setColorOnFace(CYAN, 0);
        setColorOnFace(CYAN, 1);
        setColorOnFace(CYAN, 3);
        setColorOnFace(CYAN, 4);
        break;
      }
    case splitAll:
      {
        setColor(CYAN);
        break;
      }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (buttonDoubleClicked()) {
    switch (function)
    {
      case start:
        {
          function = laser;
          type = laserR;
          break;
        }
      case laser:
        {
          function = interact;
          type = mirror;
          break;
        }
      case interact:
        {
          function = start;
          type = basic;
        }
    }
    setFaceOnClick();
  }

  if (buttonSingleClicked()) {
    switch (function)
    {
      case start:
        {
          break;
        }
      case laser:
        {
          switch (type)
          {
            case laserR:
              {
                type = laserG;
                break;
              }
            case laserG:
              {
                type = laserB;
                break;
              }
            case laserB:
              {
                type = laserR;
                break;
              }
          }
          break;
        }
      case interact:
        {
          switch (type)
          {
            case mirror:
              {
                type = split2;
                break;
              }
            case split2:
              {
                type = split3;
                break;
              }
            case split3:
              {
                type = splitAll;
                break;
              }
            case splitAll:
              {
                type = mirror;
                break;
              }
          }
          break;
        }
    }

    setFaceOnClick();
  }

  switch (type)
  {
    case basic:
      {
        FOREACH_FACE(f) {

          if (!isValueReceivedOnFaceExpired(f)) { //neighbor!

            switch (getLastValueReceivedOnFace(f))
            {
              case 1:
                {
                  int otherside = f + 3;
                  if (otherside > 5)
                    otherside = otherside - 6;

                  if (faceColors[f] == 0)
                  {
                    setColorOnFace(RED, f);
                    setColorOnFace(RED, otherside);
                    faceColors[otherside] = 1;
                  }
                  break;
                }
              case 2:
                {
                  int otherside = f + 3;
                  if (otherside > 5)
                    otherside = otherside - 6;

                  if (faceColors[f] == 0)
                  {
                    setColorOnFace(GREEN, f);
                    setColorOnFace(GREEN, otherside);
                    faceColors[otherside] = 2;
                  }
                  break;
                }
              case 3:
                {
                  int otherside = f + 3;
                  if (otherside > 5)
                    otherside = otherside - 6;

                  if (faceColors[f] == 0)
                  {
                    setColorOnFace(BLUE, f);
                    setColorOnFace(BLUE, otherside);
                    faceColors[otherside] = 3;
                  }
                  break;
                }
              default:
                {
                  if (faceColors[f] == 0) //not laser end
                  {
                    int otherside = f + 3;
                    if (otherside > 5)
                      otherside = otherside - 6;

                    setColorOnFace(OFF, f);
                    setColorOnFace(OFF, otherside);
                    faceColors[otherside] = 0;
                  }
                  break;
                }
            }
          }
          else
          {
            if (faceColors[f] == 0) //not laser end
            {
              int otherside = f + 3;
              if (otherside > 5)
                otherside = otherside - 6;

              setColorOnFace(OFF, f);
              setColorOnFace(OFF, otherside);
              faceColors[otherside] = 0;
            }
          }
        }
        break;
      }
    case mirror:
      {
        if (!isValueReceivedOnFaceExpired(4)) { //neighbor!
          switch (getLastValueReceivedOnFace(4))
          {
            case 1:
              {
                setColorOnFace(RED, 4);
                break;
              }
            case 2:
              {
                setColorOnFace(GREEN, 4);
                break;
              }
            case 3:
              {
                setColorOnFace(BLUE, 4);
                break;
              }
            default:
              {
                setColorOnFace(OFF, 4);
                break;
              }
          }
        }
        else
          setColorOnFace(OFF, 4);

        if (!isValueReceivedOnFaceExpired(3)) { //neighbor!
          switch (getLastValueReceivedOnFace(3))
          {
            case 1:
              {
                if (faceColors[3] == 0)
                {
                  setColorOnFace(RED, 3);
                  setColorOnFace(RED, 5);
                  faceColors[5] = 1;
                }
                break;
              }
            case 2:
              {
                if (faceColors[3] == 0)
                {
                  setColorOnFace(GREEN, 3);
                  setColorOnFace(GREEN, 5);
                  faceColors[5] = 2;
                }
                break;
              }
            case 3:
              {
                if (faceColors[3] == 0)
                {
                  setColorOnFace(BLUE, 3);
                  setColorOnFace(BLUE, 5);
                  faceColors[5] = 3;
                }
                break;
              }
            default:
              {
                if (faceColors[3] == 0)
                {
                  setColorOnFace(OFF, 3);
                  setColorOnFace(OFF, 5);
                  faceColors[5] = 0;
                }
                break;
              }
          }
        }
        else
        {
          if (faceColors[3] == 0)
          {
            setColorOnFace(OFF, 3);
            setColorOnFace(OFF, 5);
            faceColors[5] = 0;
          }
        }

        if (!isValueReceivedOnFaceExpired(5)) { //neighbor!
          switch (getLastValueReceivedOnFace(5))
          {
            case 1:
              {
                if (faceColors[5] == 0)
                {
                  setColorOnFace(RED, 5);
                  setColorOnFace(RED, 3);
                  faceColors[3] = 1;
                }
                break;
              }
            case 2:
              {
                if (faceColors[5] == 0)
                {
                  setColorOnFace(GREEN, 5);
                  setColorOnFace(GREEN, 3);
                  faceColors[3] = 2;
                }
                break;
              }
            case 3:
              {
                if (faceColors[5] == 0)
                {
                  setColorOnFace(BLUE, 5);
                  setColorOnFace(BLUE, 3);
                  faceColors[3] = 3;
                }
                break;
              }
            default:
              {
                if (faceColors[5] == 0)
                {
                  setColorOnFace(OFF, 5);
                  setColorOnFace(OFF, 3);
                  faceColors[3] = 0;
                }
                break;
              }
          }
        }
        else
        {
          if (faceColors[5] == 0)
          {
            setColorOnFace(OFF, 5);
            setColorOnFace(OFF, 3);
            faceColors[3] = 0;
          }
        }

        break;
      }
    case split2:
      {
        FOREACH_FACE(f) {
          if (!isValueReceivedOnFaceExpired(f)) { //neighbor!
            if (f == 0 || f == 2  || f == 4)
            {
              switch (getLastValueReceivedOnFace(f))
              {
                case 1:
                  {
                    if (faceColors[0] == 0 && faceColors[2] == 0 && faceColors[4] == 0)
                    {
                      setColorOnFace(RED, 0);
                      setColorOnFace(RED, 2);
                      setColorOnFace(RED, 4);
                      faceColors[0] = 1;
                      faceColors[2] = 1;
                      faceColors[4] = 1;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 2:
                  {
                    if (faceColors[0] == 0 && faceColors[2] == 0 && faceColors[4] == 0)
                    {
                      setColorOnFace(GREEN, 0);
                      setColorOnFace(GREEN, 2);
                      setColorOnFace(GREEN, 4);
                      faceColors[0] = 2;
                      faceColors[2] = 2;
                      faceColors[4] = 2;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 3:
                  {
                    if (faceColors[0] == 0 && faceColors[2] == 0 && faceColors[4] == 0)
                    {
                      setColorOnFace(BLUE, 0);
                      setColorOnFace(BLUE, 2);
                      setColorOnFace(BLUE, 4);
                      faceColors[0] = 3;
                      faceColors[2] = 3;
                      faceColors[4] = 3;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                default:
                  {
                    if (faceColors[f] == 0)
                    {
                      setColorOnFace(CYAN, 0);
                      setColorOnFace(CYAN, 2);
                      setColorOnFace(CYAN, 4);
                      faceColors[0] = 0;
                      faceColors[2] = 0;
                      faceColors[4] = 0;
                    }
                    break;
                  }
              }
            }
            else //1,3,5 faces
            {
              switch (getLastValueReceivedOnFace(f))
              {
                case 1:
                  {
                    if (faceColors[1] == 0 && faceColors[3] == 0 && faceColors[5] == 0)
                    {
                      setColorOnFace(RED, 1);
                      setColorOnFace(RED, 3);
                      setColorOnFace(RED, 5);
                      faceColors[1] = 1;
                      faceColors[3] = 1;
                      faceColors[5] = 1;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 2:
                  {
                    if (faceColors[1] == 0 && faceColors[3] == 0 && faceColors[5] == 0)
                    {
                      setColorOnFace(GREEN, 1);
                      setColorOnFace(GREEN, 3);
                      setColorOnFace(GREEN, 5);
                      faceColors[1] = 2;
                      faceColors[3] = 2;
                      faceColors[5] = 2;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 3:
                  {
                    if (faceColors[1] == 0 && faceColors[3] == 0 && faceColors[5] == 0)
                    {
                      setColorOnFace(BLUE, 1);
                      setColorOnFace(BLUE, 3);
                      setColorOnFace(BLUE, 5);
                      faceColors[1] = 3;
                      faceColors[3] = 3;
                      faceColors[5] = 3;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                default:
                  {
                    if (faceColors[f] == 0)
                    {
                      setColorOnFace(OFF, 1);
                      setColorOnFace(OFF, 3);
                      setColorOnFace(OFF, 5);
                      faceColors[1] = 0;
                      faceColors[3] = 0;
                      faceColors[5] = 0;
                    }
                    break;
                  }
              }
            }
          }
          else
          {
            if (f == 0 || f == 2  || f == 4)
            {
              if (faceColors[f] == 0)
              {
                setColorOnFace(CYAN, 0);
                setColorOnFace(CYAN, 2);
                setColorOnFace(CYAN, 4);
                faceColors[0] = 0;
                faceColors[2] = 0;
                faceColors[4] = 0;
              }
            }
            else
            {
              if (faceColors[f] == 0)
              {
                setColorOnFace(OFF, 1);
                setColorOnFace(OFF, 3);
                setColorOnFace(OFF, 5);
                faceColors[1] = 0;
                faceColors[3] = 0;
                faceColors[5] = 0;
              }
            }
          }
        }
        break;
      }
    case split3:
      {
        FOREACH_FACE(f) {
          if (!isValueReceivedOnFaceExpired(f)) { //neighbor!
            if (f == 0 || f == 1  || f == 3 || f == 4)
            {
              switch (getLastValueReceivedOnFace(f))
              {
                case 1:
                  {
                    if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                    {
                      setColorOnFace(RED, 0);
                      setColorOnFace(RED, 1);
                      setColorOnFace(RED, 3);
                      setColorOnFace(RED, 4);
                      faceColors[0] = 1;
                      faceColors[1] = 1;
                      faceColors[3] = 1;
                      faceColors[4] = 1;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 2:
                  {
                    if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                    {
                      setColorOnFace(GREEN, 0);
                      setColorOnFace(GREEN, 1);
                      setColorOnFace(GREEN, 3);
                      setColorOnFace(GREEN, 4);
                      faceColors[0] = 2;
                      faceColors[1] = 2;
                      faceColors[3] = 2;
                      faceColors[4] = 2;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                case 3:
                  {
                    if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                    {
                      setColorOnFace(BLUE, 0);
                      setColorOnFace(BLUE, 1);
                      setColorOnFace(BLUE, 3);
                      setColorOnFace(BLUE, 4);
                      faceColors[0] = 3;
                      faceColors[1] = 3;
                      faceColors[3] = 3;
                      faceColors[4] = 3;
                      faceColors[f] = 0;
                    }
                    break;
                  }
                default:
                  {
                    if (faceColors[f] == 0)
                    {
                      setColorOnFace(CYAN, 0);
                      setColorOnFace(CYAN, 1);
                      setColorOnFace(CYAN, 3);
                      setColorOnFace(CYAN, 4);
                      faceColors[0] = 0;
                      faceColors[1] = 0;
                      faceColors[3] = 0;
                      faceColors[4] = 0;
                    }
                    break;
                  }
              }
            }
          }
          else
          {
            if (f == 0 || f == 1  || f == 3 || f == 4)
            {
              if (faceColors[f] == 0)
              {
                setColorOnFace(CYAN, 0);
                setColorOnFace(CYAN, 1);
                setColorOnFace(CYAN, 3);
                setColorOnFace(CYAN, 4);
                faceColors[0] = 0;
                faceColors[1] = 0;
                faceColors[3] = 0;
                faceColors[4] = 0;
              }
            }
          }
        }
        break;
      }
    case splitAll:
      {
        FOREACH_FACE(f) {
          if (!isValueReceivedOnFaceExpired(f)) { //neighbor!
            switch (getLastValueReceivedOnFace(f))
            {
              case 1:
                {
                  if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                  {
                    setColor(RED);
                    faceColors[0] = 1;
                    faceColors[1] = 1;
                    faceColors[2] = 1;
                    faceColors[3] = 1;
                    faceColors[4] = 1;
                    faceColors[5] = 1;
                    faceColors[f] = 0;
                  }
                  break;
                }
              case 2:
                {
                  if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                  {
                    setColor(GREEN);
                    faceColors[0] = 2;
                    faceColors[1] = 2;
                    faceColors[2] = 2;
                    faceColors[3] = 2;
                    faceColors[4] = 2;
                    faceColors[5] = 2;
                    faceColors[f] = 0;
                  }
                  break;
                }
              case 3:
                {
                  if (faceColors[0] == 0 && faceColors[1] == 0) //checking 2 is enough
                  {
                    setColor(BLUE);
                    faceColors[0] = 3;
                    faceColors[1] = 3;
                    faceColors[2] = 3;
                    faceColors[3] = 3;
                    faceColors[4] = 3;
                    faceColors[5] = 3;
                    faceColors[f] = 0;
                  }
                  break;
                }
              default:
                {
                  if (faceColors[f] == 0)
                  {
                    setColor(CYAN);
                    faceColors[0] = 0;
                    faceColors[1] = 0;
                    faceColors[2] = 0;
                    faceColors[3] = 0;
                    faceColors[4] = 0;
                    faceColors[5] = 0;
                  }
                  break;
                }
            }
          }
          else
          {
            if (faceColors[f] == 0)
            {
              setColor(CYAN);
              faceColors[0] = 0;
              faceColors[1] = 0;
              faceColors[2] = 0;
              faceColors[3] = 0;
              faceColors[4] = 0;
              faceColors[5] = 0;
            }
          }
        }
        break;
      }
  }
  //set communications
  FOREACH_FACE(f) {
    setValueSentOnFace(faceColors[f], f);
  }
}
