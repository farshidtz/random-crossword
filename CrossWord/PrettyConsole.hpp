/*
  version : 1Feb2010
  Copyright (C) 2010 Victor Soh Chien Ming <cmsoh@mmu.edu.my>

  The following code should work on Windows 2000 and above
*/
#ifndef PrettyConsole_hpp
#define PrettyConsole_hpp
struct RGBI
{
    bool r;// red
    bool g;// green
    bool b;// blue
    bool i;// intensity
    RGBI( bool r=false, bool g=false, bool b=false, bool i=false );
};
void setTextColor( RGBI const& foreground               ,
                   RGBI const& background=RGBI(0,0,0,0) );
void setCursorXY( int x, int y );
#endif
