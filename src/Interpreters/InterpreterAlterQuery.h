#pragma once

#include <Interpreters/IInterpreter.h>
#include <Parsers/IAST_fwd.h>


namespace DB
{

class AccessRightsElements;
class ASTAlterCommand;
class ASTAlterQuery;


/** Allows you add or remove a column in the table.
  * It also allows you to manipulate the partitions of the MergeTree family tables.
  */
class InterpreterAlterQuery : public IInterpreter, WithContext
{
public:
    InterpreterAlterQuery(const ASTPtr & query_ptr_, ContextPtr context_);

    BlockIO execute() override;

    static AccessRightsElements getRequiredAccessForCommand(const ASTAlterCommand & command, const String & database, const String & table);

    void extendQueryLogElemImpl(QueryLogElement & elem, const ASTPtr & ast, ContextPtr context) const override;

    bool supportsTransactions() const override { return true; }

private:
    AccessRightsElements getRequiredAccess() const;

    BlockIO executeToTable(ASTAlterQuery & alter);

    BlockIO executeToDatabase(const ASTAlterQuery & alter);

    ASTPtr query_ptr;
};

}
