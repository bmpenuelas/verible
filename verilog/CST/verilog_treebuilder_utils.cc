// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "verilog/CST/verilog_treebuilder_utils.h"

#include <memory>
#include <string>

#include "absl/strings/string_view.h"
#include "common/text/concrete_syntax_leaf.h"
#include "common/text/concrete_syntax_tree.h"
#include "common/text/symbol.h"
#include "common/text/token_info.h"
#include "common/util/logging.h"
#include "verilog/CST/verilog_nonterminals.h"

namespace verilog {

using verible::down_cast;

// Set of utility functions for embedded a statement into a certain context.
std::string EmbedInClass(const std::string& text) {
  return "class test_class;\n" + text + "\nendclass\n";
}

std::string EmbedInModule(const std::string& text) {
  return "module test_module;\n" + text + "\nendmodule\n";
}

std::string EmbedInFunction(const std::string& text) {
  return "function integer test_function;\n" + text + "\nendfunction\n";
}

std::string EmbedInClassMethod(const std::string& text) {
  return EmbedInClass(EmbedInFunction(text));
}

bool EqualNodeTag(const verible::SymbolPtr& symbol, NodeEnum e) {
  if (symbol == nullptr || symbol->Kind() != verible::SymbolKind::kNode)
    return false;

  const auto* node_ptr =
      down_cast<const verible::SyntaxTreeNode*>(symbol.get());
  return node_ptr->MatchesTag(e);
}

void ExpectString(const verible::SymbolPtr& symbol,
                  const std::string& expected) {
  const auto* leaf = down_cast<const verible::SyntaxTreeLeaf*>(symbol.get());
  CHECK_EQ(std::string(ABSL_DIE_IF_NULL(leaf)->get().text), expected);
}

}  // namespace verilog
