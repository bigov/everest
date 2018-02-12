#ifndef __EV_APP_HPP__
#define __EV_APP_HPP__

#include "main.hpp"
#include "frame.hpp"
#include "fields.hpp"
#include "text.hpp"

namespace ev {

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class app : public wxApp
{
  public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;

    void CreateStyles();
    wxRichTextStyleSheet* m_styleSheet;
    wxRichTextStyleSheet* GetStyleSheet() const { return m_styleSheet; }

  #if wxUSE_PRINTING_ARCHITECTURE
    wxRichTextPrinting* m_printing;
    wxRichTextPrinting* GetPrinting() const { return m_printing; }
  #endif
};

} //namespace ev
#endif // __EV_APP_HPP__
