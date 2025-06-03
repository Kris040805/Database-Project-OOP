#pragma once
#include "Table.hpp"
#include <vector>
#include <string>
#include <unordered_map>

/**
 * @class Database
 * @brief Manages all tables and their file associations in the database.
 *
 * The Database class provides methods for adding, retrieving, and renaming tables,
 * as well as for managing the mapping between table names and their corresponding file names.
 * It also stores the name of the currently opened catalog file.
 */
class Database {
private:
    std::vector<Table> tables; ///< List of all tables in the database.
    std::unordered_map<std::string, std::string> tableNameToFileName; ///< Maps table names to their file names.
    std::string catalogFileName; ///< Name of the currently opened catalog file.

public:
    /**
     * @brief Adds a new table to the database.
     * @param table Reference to the table to add.
     * @throws std::invalid_argument If a table with the same name already exists.
     */
    void addTable(const Table& table);

    /**
     * @brief Retrieves a table by name.
     * @param name The name of the table.
     * @return Reference to the table.
     * @throws std::invalid_argument If the table does not exist.
     */
    Table& getTableByName(const std::string& name);

    /**
     * @brief Checks if a table with the given name exists.
     * @param name The name of the table.
     * @return True if the table exists, false otherwise.
     */
    bool hasTable(const std::string& name) const;

    /**
     * @brief Returns a list of all table names in the database.
     * @return Vector of table names.
     */
    std::vector<std::string> listTableNames() const;

    /**
     * @brief Renames an existing table.
     * @param oldName The current name of the table.
     * @param newName The new name for the table.
     */
    void renameTable(const std::string& oldName, const std::string& newName);

    /**
     * @brief Sets the name of the currently opened catalog file.
     * @param fileName The catalog file name.
     */
    void setCatalogFileName(const std::string& fileName);

    /**
     * @brief Gets the name of the currently opened catalog file.
     * @return Reference to the catalog file name.
     */
    const std::string& getCatalogFileName() const;

    /**
     * @brief Unregisters the file associated with a table.
     * @param tabName The name of the table.
     */
    void unregisterTableFile(const std::string& tabName);
    
    /**
     * @brief Registers a file for a table.
     * @param tabName The name of the table.
     * @param fileName The file name to associate with the table.
     */
    void registerTableFile(const std::string& tabName, const std::string& fileName);
    
    /**
     * @brief Gets the file name associated with a table.
     * @param tabName The name of the table.
     * @return The file name associated with the table.
     * @throws std::invalid_argument If the table does not exist.
     */
    std::string getFileName(const std::string& tabName) const;
};