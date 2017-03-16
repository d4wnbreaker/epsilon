#include "curve_parameter_controller.h"
#include "graph_controller.h"
#include <assert.h>

using namespace Shared;

namespace Sequence {

CurveParameterController::CurveParameterController(GraphController * graphController, InteractiveCurveViewRange * graphRange, CurveViewCursor * cursor) :
  FunctionCurveParameterController(graphRange, cursor, "n"),
  m_sumCell(PointerTableCell((char*)"Somme des termes")),
  m_graphController(graphController)
{
}

const char * CurveParameterController::title() const {
  return "Options de la suite";
}

bool CurveParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK) {
    switch (m_selectableTableView.selectedRow()) {
      case 0:
      {
        StackViewController * stack = (StackViewController *)parentResponder();
        stack->pop();
        stack->push(m_graphController->termSumController());
        return true;
      }
      case 1:
        return handleGotoSelection();
      default:
        return false;
    }
  }
  return false;
}

int CurveParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};

HighlightCell * CurveParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  HighlightCell * cells[] = {&m_sumCell, &m_goToCell};
  return cells[index];
}

int CurveParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

}