"""
CRUD_Python_Module.py

CS-340 Client/Server Development - Project One CRUD module, reused in Project Two.
Author: Ziyan Noorani

Provides the AnimalShelter class, which wraps a PyMongo connection to the
Austin Animal Center (AAC) database and exposes Create, Read, Update and
Delete operations on the "animals" collection. In the dashboard's MVC
structure, this module is the bridge between the controller (Dash callbacks)
and the model (MongoDB).
"""

from pymongo import MongoClient
from pymongo.errors import PyMongoError


class AnimalShelter(object):
    """CRUD operations for the animals collection in MongoDB."""

    def __init__(self, username, password,
                 host='localhost', port=27017,
                 db_name='aac', collection='animals',
                 auth_source='admin'):
        """
        Open an authenticated connection to MongoDB.

        :param username: MongoDB user (aacuser for this course)
        :param password: password for that user
        :param host: MongoDB host name (Codio runs mongod on localhost)
        :param port: MongoDB port (default 27017)
        :param db_name: database that holds the AAC data
        :param collection: collection that holds the animal records
        :param auth_source: database the user account was created on
        """
        self.client = MongoClient(
            host=host,
            port=port,
            username=username,
            password=password,
            authSource=auth_source,
        )
        self.database = self.client[db_name]
        self.collection = self.database[collection]

    # ------------------------------------------------------------------
    # C in CRUD
    # ------------------------------------------------------------------
    def create(self, data):
        """
        Insert one document into the collection.

        :param data: dictionary of key/value pairs for the new document
        :return: True if the insert succeeded, otherwise False
        """
        if not data or not isinstance(data, dict):
            raise ValueError("create() requires a non-empty dictionary")
        try:
            result = self.collection.insert_one(data)
            return result.acknowledged
        except PyMongoError as err:
            print(f"Create failed: {err}")
            return False

    # ------------------------------------------------------------------
    # R in CRUD
    # ------------------------------------------------------------------
    def read(self, query=None):
        """
        Find documents that match a query.

        :param query: dictionary filter; an empty dict or None returns all
        :return: list of matching documents (empty list on error)
        """
        if query is None:
            query = {}
        if not isinstance(query, dict):
            raise ValueError("read() requires a dictionary query")
        try:
            # Return a list instead of a cursor so callers such as
            # pandas.DataFrame.from_records() can use the result directly.
            return list(self.collection.find(query))
        except PyMongoError as err:
            print(f"Read failed: {err}")
            return []

    # ------------------------------------------------------------------
    # U in CRUD
    # ------------------------------------------------------------------
    def update(self, query, new_values):
        """
        Update every document that matches a query.

        :param query: dictionary filter for the documents to change
        :param new_values: dictionary of fields to set, e.g. {"name": "Max"}
        :return: number of documents modified
        """
        if not isinstance(query, dict) or not isinstance(new_values, dict) or not new_values:
            raise ValueError("update() requires a query dict and a non-empty update dict")
        try:
            result = self.collection.update_many(query, {"$set": new_values})
            return result.modified_count
        except PyMongoError as err:
            print(f"Update failed: {err}")
            return 0

    # ------------------------------------------------------------------
    # D in CRUD
    # ------------------------------------------------------------------
    def delete(self, query):
        """
        Delete every document that matches a query.

        :param query: dictionary filter for the documents to remove
        :return: number of documents deleted
        """
        if not query or not isinstance(query, dict):
            # Block an empty filter so a mistake can't wipe the collection
            raise ValueError("delete() requires a non-empty dictionary query")
        try:
            result = self.collection.delete_many(query)
            return result.deleted_count
        except PyMongoError as err:
            print(f"Delete failed: {err}")
            return 0