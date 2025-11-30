#!/usr/bin/env python3
"""
MCP Server for COIN-OR Knowledge Base

Provides tools for querying optimization solver annotations:
- search_algorithms: Find implementations of specific algorithms
- search_math: Find files with specific mathematical concepts
- get_library: Get overview and files for a library
- get_file: Get all annotations for a specific file
- list_algorithms: List all documented algorithms

Run: python coin_or_kb_server.py
"""

import json
import re
import sys
from pathlib import Path
from typing import Any

# MCP protocol via stdio
def send_response(response: dict):
    """Send JSON-RPC response to stdout."""
    msg = json.dumps(response)
    sys.stdout.write(f"Content-Length: {len(msg)}\r\n\r\n{msg}")
    sys.stdout.flush()

def read_request() -> dict:
    """Read JSON-RPC request from stdin."""
    headers = {}
    while True:
        line = sys.stdin.readline()
        if line == '\r\n' or line == '\n':
            break
        if ':' in line:
            key, value = line.split(':', 1)
            headers[key.strip().lower()] = value.strip()

    content_length = int(headers.get('content-length', 0))
    if content_length > 0:
        body = sys.stdin.read(content_length)
        return json.loads(body)
    return {}


class CoinORKnowledgeBase:
    """Knowledge base loaded from annotations.json."""

    def __init__(self, json_path: Path = None):
        if json_path is None:
            # Try common locations
            for p in [
                Path(__file__).parent.parent / 'site/static/api/annotations.json',
                Path('site/static/api/annotations.json'),
                Path('annotations.json'),
            ]:
                if p.exists():
                    json_path = p
                    break

        if json_path and json_path.exists():
            with open(json_path) as f:
                self.data = json.load(f)
        else:
            self.data = {"layers": {}, "stats": {}}

    def search_algorithms(self, query: str) -> list[dict]:
        """Search for files implementing algorithms matching query."""
        results = []
        query_lower = query.lower()

        for layer_name, layer in self.data.get('layers', {}).items():
            for lib_name, lib in layer.get('libraries', {}).items():
                for file_path, file_data in lib.get('files', {}).items():
                    algorithm = file_data.get('algorithm', '')
                    if query_lower in algorithm.lower():
                        results.append({
                            'layer': layer_name,
                            'library': lib_name,
                            'file': file_path,
                            'algorithm': algorithm[:500],
                            'brief': file_data.get('brief', ''),
                            'complexity': file_data.get('complexity', ''),
                        })
        return results

    def search_math(self, query: str) -> list[dict]:
        """Search for files with mathematical concepts matching query."""
        results = []
        query_lower = query.lower()

        for layer_name, layer in self.data.get('layers', {}).items():
            for lib_name, lib in layer.get('libraries', {}).items():
                for file_path, file_data in lib.get('files', {}).items():
                    math = file_data.get('math', '')
                    if query_lower in math.lower():
                        results.append({
                            'layer': layer_name,
                            'library': lib_name,
                            'file': file_path,
                            'math': math[:500],
                            'brief': file_data.get('brief', ''),
                        })
        return results

    def get_library(self, name: str) -> dict:
        """Get overview and files for a library."""
        name_lower = name.lower()

        for layer_name, layer in self.data.get('layers', {}).items():
            for lib_name, lib in layer.get('libraries', {}).items():
                if lib_name.lower() == name_lower:
                    # Summarize files with pass2 annotations
                    pass2_files = [
                        {'file': f, 'brief': d.get('brief', ''), 'algorithm': d.get('algorithm', '')[:200]}
                        for f, d in lib.get('files', {}).items()
                        if d.get('has_pass2')
                    ]
                    return {
                        'name': lib_name,
                        'layer': layer_name,
                        'file_count': lib.get('file_count', 0),
                        'pass2_count': lib.get('pass2_count', 0),
                        'pass2_files': pass2_files,
                    }
        return {'error': f'Library {name} not found'}

    def get_file(self, library: str, file_path: str) -> dict:
        """Get all annotations for a specific file."""
        lib_lower = library.lower()

        for layer_name, layer in self.data.get('layers', {}).items():
            for lib_name, lib in layer.get('libraries', {}).items():
                if lib_name.lower() == lib_lower:
                    for f, data in lib.get('files', {}).items():
                        if file_path in f:
                            return {
                                'layer': layer_name,
                                'library': lib_name,
                                'file': f,
                                **data
                            }
        return {'error': f'File {file_path} not found in {library}'}

    def list_algorithms(self) -> list[dict]:
        """List all documented algorithms."""
        algorithms = []

        for layer_name, layer in self.data.get('layers', {}).items():
            for lib_name, lib in layer.get('libraries', {}).items():
                for file_path, file_data in lib.get('files', {}).items():
                    if file_data.get('algorithm'):
                        # Extract algorithm name (first line usually)
                        algo = file_data['algorithm']
                        name = algo.split('\n')[0].split(':')[0].strip()
                        algorithms.append({
                            'name': name,
                            'library': lib_name,
                            'file': file_path,
                            'complexity': file_data.get('complexity', '').split('\n')[0],
                        })
        return algorithms

    def get_stats(self) -> dict:
        """Get knowledge base statistics."""
        return self.data.get('stats', {})


# Global knowledge base instance
kb = CoinORKnowledgeBase()


def handle_initialize(params: dict) -> dict:
    """Handle initialize request."""
    return {
        "protocolVersion": "2024-11-05",
        "capabilities": {
            "tools": {},
            "resources": {},
        },
        "serverInfo": {
            "name": "coin-or-kb",
            "version": "1.0.0",
        }
    }


def handle_tools_list() -> dict:
    """Return list of available tools."""
    return {
        "tools": [
            {
                "name": "search_algorithms",
                "description": "Search for files implementing specific algorithms (e.g., 'LU factorization', 'Dijkstra', 'simplex')",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "query": {"type": "string", "description": "Algorithm name or keyword to search"}
                    },
                    "required": ["query"]
                }
            },
            {
                "name": "search_math",
                "description": "Search for files with specific mathematical concepts (e.g., 'Ax=b', 'clique', 'bound tightening')",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "query": {"type": "string", "description": "Math concept or formula to search"}
                    },
                    "required": ["query"]
                }
            },
            {
                "name": "get_library",
                "description": "Get overview of a library including its annotated files",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "name": {"type": "string", "description": "Library name (e.g., 'CoinUtils', 'Clp', 'Ipopt')"}
                    },
                    "required": ["name"]
                }
            },
            {
                "name": "get_file",
                "description": "Get all annotations for a specific file",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "library": {"type": "string", "description": "Library name"},
                        "file": {"type": "string", "description": "File path or name"}
                    },
                    "required": ["library", "file"]
                }
            },
            {
                "name": "list_algorithms",
                "description": "List all documented algorithms in the knowledge base",
                "inputSchema": {
                    "type": "object",
                    "properties": {}
                }
            },
            {
                "name": "get_stats",
                "description": "Get knowledge base statistics (file counts, coverage)",
                "inputSchema": {
                    "type": "object",
                    "properties": {}
                }
            },
        ]
    }


def handle_tool_call(name: str, arguments: dict) -> dict:
    """Execute a tool call."""
    if name == "search_algorithms":
        results = kb.search_algorithms(arguments.get("query", ""))
        return {"content": [{"type": "text", "text": json.dumps(results, indent=2)}]}

    elif name == "search_math":
        results = kb.search_math(arguments.get("query", ""))
        return {"content": [{"type": "text", "text": json.dumps(results, indent=2)}]}

    elif name == "get_library":
        result = kb.get_library(arguments.get("name", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "get_file":
        result = kb.get_file(arguments.get("library", ""), arguments.get("file", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "list_algorithms":
        results = kb.list_algorithms()
        return {"content": [{"type": "text", "text": json.dumps(results, indent=2)}]}

    elif name == "get_stats":
        result = kb.get_stats()
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    return {"content": [{"type": "text", "text": f"Unknown tool: {name}"}], "isError": True}


def handle_resources_list() -> dict:
    """Return list of available resources."""
    return {
        "resources": [
            {
                "uri": "coinor://annotations",
                "name": "Full Annotations JSON",
                "description": "Complete knowledge base as JSON",
                "mimeType": "application/json"
            }
        ]
    }


def handle_resource_read(uri: str) -> dict:
    """Read a resource."""
    if uri == "coinor://annotations":
        return {
            "contents": [
                {
                    "uri": uri,
                    "mimeType": "application/json",
                    "text": json.dumps(kb.data)
                }
            ]
        }
    return {"contents": [], "error": f"Unknown resource: {uri}"}


def main():
    """Main MCP server loop."""
    while True:
        try:
            request = read_request()
            if not request:
                continue

            method = request.get('method', '')
            params = request.get('params', {})
            req_id = request.get('id')

            result = None
            error = None

            if method == 'initialize':
                result = handle_initialize(params)
            elif method == 'tools/list':
                result = handle_tools_list()
            elif method == 'tools/call':
                result = handle_tool_call(params.get('name', ''), params.get('arguments', {}))
            elif method == 'resources/list':
                result = handle_resources_list()
            elif method == 'resources/read':
                result = handle_resource_read(params.get('uri', ''))
            elif method == 'notifications/initialized':
                continue  # No response needed
            else:
                error = {"code": -32601, "message": f"Unknown method: {method}"}

            if req_id is not None:
                response = {"jsonrpc": "2.0", "id": req_id}
                if error:
                    response["error"] = error
                else:
                    response["result"] = result
                send_response(response)

        except Exception as e:
            sys.stderr.write(f"Error: {e}\n")
            sys.stderr.flush()


if __name__ == '__main__':
    main()
