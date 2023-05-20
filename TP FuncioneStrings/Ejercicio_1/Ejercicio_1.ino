#define email "amp.com"
#define pass "hola123"
  
String lecturaEmail;
String lecturaPass;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Ingresar Email: ");
}

void loop() 
{ 
  while (Serial.available() == 0){}
  lecturaEmail = Serial.readString();
  Serial.println("Ingresar contraseña:  ");
  
  while (Serial.available() == 0){}
  lecturaPass = Serial.readString();
  
  if (checkUserPassword(lecturaEmail, lecturaPass))
  {
    Serial.println("Bienvenide"); 
  }
  else if (!checkUserPassword(lecturaEmail, lecturaPass))
  {
    Serial.println("Email o contraseña incorrecta");
    Serial.println("Ingresar Email: ");
  }
}

boolean checkUserPassword (String checkEmail, String checkPass)
{
  if (checkEmail == email && checkPass == pass)
  {
    return(true);
  }
  else if (checkEmail != email || checkPass != pass)
  {
    return(false);
  }
}
