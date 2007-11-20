//
//  SuperTuxKart - a fun racing game with go-kart
//  This code originally from Neverball copyright (C) 2003 Robert Kooima
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_WIDGET_MANAGER_H
#define HEADER_WIDGET_MANAGER_H

#include "widget.hpp"

#include <vector>

/* Here are some big-picture instructions about how to use this widget
 * manager: the extern widget_manager is a global interface to the class. Call
 * add_wgt() to specify the widgets you want, and for each widget specify the
 * details of it with the 'switch features', that can be changed between
 * show/hide, the initial setting for all of them is to be hidden. You will
 * usually have to call it's set_*() function, then the show_*() functions.
 * After you have defined all the widgets in the screen, call layout(), that
 * will do the actual work at creating the widgets. Call the activated
 * functions during the time the widgets are alive, and make sure that
 * update() is called each frame.
 *
 * You can use set_initial_*state() to avoid setting the state of the same
 * switch features with same values over and over; the default states are
 * reset when you call layout() or you can use reset_default_states().
 */


class WidgetManager
{
    struct WidgetID
    {
        int token;
        bool active; //If true, then this widget is interactive(though by
                       //definition, widgets are supposed to be interactive).

        //The percentages of the container this widget takes
        int min_width;
        int min_height;

        Widget *widget;
    };

    std::vector<WidgetID> m_widgets;
    std::vector<int> m_breaks;

    int m_x;
    int m_y;

    int m_selected_wgt_token;

    //TODO: change 'default' to 'initial'
    bool m_default_active;
    bool m_default_show_rect;
    bool m_default_rect_round_corners;
    const GLfloat *m_default_rect_color;
    bool m_default_show_texture;
    int m_default_texture;
    bool m_default_show_text;
    std::string m_default_text;
    WidgetFontSize m_default_text_size;
    Font::FontAlignType m_default_text_x_alignment;
    Font::FontAlignType m_default_text_y_alignment;

    bool m_default_enable_scroll;
/*    int m_default_scroll_x_pos;*/
    int m_default_scroll_y_pos;
/*    int m_default_scroll_x_speed;*/
    int m_default_scroll_y_speed;

    bool line_breaks( const int WGT ) const;

    int find_id(const int TOKEN) const;
    int calc_width() const;
    int calc_height() const;
    int calc_line_width(const int START_WGT) const;
    int calc_line_height(const int START_WGT) const;

    int find_left_widget(const int START_WGT) const;
    int find_right_widget(const int START_WGT) const;
    int find_top_widget(const int START_WGT) const;
    int find_bottom_widget(const int START_WGT) const;

public:
    //FIXME: maybe I should get this out of this class?
    static const int WGT_NONE;

    WidgetManager();
    ~WidgetManager();

    bool add_wgt
    (
        const int TOKEN, //A number that names the widget.
        const int MIN_WIDTH, //These values are percentages not pixels. If
                             //the widget is inside a container, 100%
                             //represents container space, otherwise 100% is
                             //the screen space.
        const int MIN_HEIGHT
    );
    bool break_line();

    void delete_wgts();

    void update(const float DELTA);

    //TODO: WGT_AREA_NONE and WGT_AREA_ALL should have some difference.
    //Both WGT_AREA_NONE and WGT_AREA_ALL will produce centered widgets.
    bool layout( const WidgetArea POSITION );

    //TODO: make all get functions const
    int get_selected_wgt() const { return m_selected_wgt_token;}
    void set_selected_wgt(const int TOKEN);

    /* On/off widget switch features. They are all disabled/hidden initially. */
    void set_initial_activation_state( const bool ACTIVE);
    void set_initial_rect_state(const bool SHOW, const WidgetArea ROUND_CORNERS, const GLfloat* const COLOR );
    void set_initial_texture_state(const bool SHOW, const int TEXTURE );
    void set_initial_text_state
    (
        const bool SHOW,
        const std::string TEXT,
        const WidgetFontSize SIZE,
        const Font::FontAlignType X_ALIGN,
        const Font::FontAlignType Y_ALIGN
    );
    void set_initial_scroll_state(const bool ENABLE, /*const int X_POS,*/ const int Y_POS, /*const int X_SPEED, */const int Y_SPEED );
    void restore_default_states();

    void activate_wgt(const int TOKEN);
    void deactivate_wgt(const int TOKEN);

    //FIXME: maybe this should be set_wgt_rect_color ? and put after the other rect funcs?
    void set_wgt_color(const int TOKEN, const GLfloat* const COLOR);
    void set_wgt_round_corners(const int TOKEN, const WidgetArea CORNERS);
    void show_wgt_rect(const int TOKEN);
    void hide_wgt_rect(const int TOKEN);
//    void toggle_wgt_rect(const int TOKEN);

    void set_wgt_texture(const int TOKEN, const int TEXTURE);
    void show_wgt_texture(const int TOKEN);
    void hide_wgt_texture(const int TOKEN);
//    void toggle_wgt_texture(const int TOKEN);

    void set_wgt_text( const int TOKEN, const char* TEXT );
    void set_wgt_text( const int TOKEN, const std::string TEXT );
    void set_wgt_text_size( const int TOKEN, const WidgetFontSize SIZE);
    void show_wgt_text( const int TOKEN );
    void hide_wgt_text( const int TOKEN );
//    void toggle_wgt_text( const int TOKEN );
    void set_wgt_text_x_alignment( const int TOKEN, const Font::FontAlignType ALIGN );
    void set_wgt_text_y_alignment( const int TOKEN, const Font::FontAlignType ALIGN );

    void enable_wgt_scroll( const int TOKEN );
    void disable_wgt_scroll( const int TOKEN );
/*    void set_wgt_x_scroll_pos( const int TOKEN, const int POS );*/
    void set_wgt_y_scroll_pos( const int TOKEN, const int POS );
/*    void set_wgt_x_scroll_speed( const int TOKEN, const int SPEED );*/
    void set_wgt_y_scroll_speed( const int TOKEN, const int SPEED );

    /* Activated widget features. */
    void pulse_wgt( const int TOKEN ) const;

    /* Convenience widget functions. */
    void lighten_wgt_color(const int TOKEN);
    void darken_wgt_color(const int TOKEN);

    /* Input device handling. */
    int handle_mouse( const int X, const int Y );
    int handle_keyboard( const int KEY );
    int handle_joystick( int axis, int dir, int value );
};

extern WidgetManager *widget_manager;

#endif

/* EOF */
