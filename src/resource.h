/***************************************************************************
                          resource.h  -  description
                             -------------------
    begin                : Πεμ Ιαν 20 17:36:13 EET 2000
    copyright            : (C) 2000 by Panos Katsaloulis
    url                  : http://www.panayotis.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef RESOURCE_H
#define RESOURCE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


///////////////////////////////////////////////////////////////////
// resource.h  -- contains macros used for commands

///////////////////////////////////////////////////////////////////
// General application values
#define IDS_APP_ABOUT               "         KBoxes!\nVersion " VERSION \
                                    "\n(c) 1994-2000 by Panos Katsaloulis" \
									"\n\n Please send bugs and reports to http://www.panayotis.com"

#define IDS_APP_HOWTO				"            * HOW TO PLAY *\n\n" \
								"   The purpose of this game is to wipe out \n" \
								"horizontal lines of boxes, but not the last \n" \
								"one. You can wipe out as mane or as little \n" \
								"boxes as yo want, as long as they are in the\n" \
								"same horizontal line and there is not any box in\n" \
								"between which is alerady wiped out. However, you\n" \
								"can wipe out any box (or boxes), no matter if \n" \
								"they are in the beginning or in the middle of the\n" \
								"physical line. The person who wipes out the last\n" \
								"box is the looser.\n" \
								"   To play this game you have to select at the first\n" \
								"box you want to wipe out and then at the last box. If \n" \
								"you want to wipe out only one box, click at it again.\n"
/* \
								"The face to the right shows the condition of the\n" \
								"computer. If it smiles, it is almost certain that you\n" \
								"are goining to loose this game..."
*/
#define IDS_STATUS_DEFAULT          "Ready."

#endif // RESOURCE_H
