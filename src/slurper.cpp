/*
 * Slurp - a web crawler
 * Copyright (C) 2011 Joseph Max DeLiso

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QString>
#include <QDebug>

#include "globals.h"
#include "util.h"
#include "eventer.h"

namespace slurp{

const char* USAGE_MESSAGE = "slurp [options] urls ...";

const char* HELP_MENU = 
" slurp - a web crawler\n"\
"   usage: slurp [options] urls ...\n"\
"   where options are some combination of the following:\n"\
"     v - verbose\n"\
"     h - display this menu and exit\n"\
"     V - display version information exit\n"\
"     n - number of URIs to crawl\n"\
"     t - maximum number of threads to use\n"\
"   note: you cannot combine options, so -vn3 is not legal\n"\
"   instead, use -v -n3 or -v -n 3\n";	

const char* LICENSE_INFO =
"Copyright (C) 2011 Joseph Max DeLiso\n\n"\
"This program is free software: you can redistribute it and/or modify\n"\
"it under the terms of the GNU General Public License as published by\n"\
"the Free Software Foundation, version 3 of the License.\n\n"\
"This program is distributed in the hope that it will be useful,\n"\
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
"GNU General Public License for more details.\n\n"\
"You should have received a copy of the GNU General Public License\n"\
"along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";

int main(int argc, char** argv, char** env) {
  int ret, flags, quota = -1, maxThreads = QThread::idealThreadCount();
  QQueue<QString> seedURIs;

  initLibraries();

  flags = validateArgs( argc, argv, env, seedURIs, quota, maxThreads );

  if( flags & FLAGS_VERBOSE ) {
    qDebug() << "debug: creating eventer instance with "
	      << seedURIs.size() << " seed URI(s) and a quota of " 
	      << quota;
  }

  Eventer ev(seedURIs, quota, flags);

  ret = ev.run(); 

  return ret;
}

} /* namespace slurp */

int main( int argc, char** argv, char ** env ) {
    return slurp::main( argc, argv, env );
}
