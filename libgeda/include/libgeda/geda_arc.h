/* gEDA - GPL Electronic Design Automation
 * libgeda - gEDA's library
 * Copyright (C) 1998-2010 Ales Hvezda
 * Copyright (C) 1998-2010 gEDA Contributors (see ChangeLog for details)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*! \file geda_arc.h
 *
 *  \brief Low-level mathematical functions for arcs
 */

typedef struct _GedaArc GedaArc;

struct _GedaArc
{
  gint x;
  gint y;

  gint radius;

  gint start_angle;
  gint sweep_angle;
};

GedaArc*
geda_arc_new ();

void
geda_arc_free (GedaArc *arc);

gboolean
geda_arc_within_sweep (const GedaArc *arc, gint x, gint y);
