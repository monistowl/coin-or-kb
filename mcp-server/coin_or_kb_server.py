#!/usr/bin/env python3
"""
MCP Server for COIN-OR Knowledge Base

Provides tools for querying optimization solver annotations and knowledge graph:

Annotation Tools:
- search_algorithms: Find implementations of specific algorithms
- search_math: Find files with specific mathematical concepts
- get_library: Get overview and files for a library
- get_file: Get all annotations for a specific file
- list_algorithms: List all documented algorithms

Knowledge Graph Tools:
- explore_concept: Get concept details and relationships
- find_path: Navigate between concepts
- prerequisites_for: Get learning dependencies for a concept
- implementations_of: Find source files for a concept
- search_concepts: Search concepts by keyword
- list_concepts: List all concepts, optionally by category

Run: python coin_or_kb_server.py
"""

import json
import re
import sys
from pathlib import Path
from typing import Any

from knowledge_graph import KnowledgeGraph

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


# Global knowledge base instances
kb = CoinORKnowledgeBase()
kg = KnowledgeGraph()


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
            # Knowledge Graph Tools
            {
                "name": "explore_concept",
                "description": "Get concept details and relationships (e.g., 'interior_point_method', 'KKT_conditions', 'branch_and_bound')",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "concept_id": {"type": "string", "description": "Concept ID or name to explore"}
                    },
                    "required": ["concept_id"]
                }
            },
            {
                "name": "find_path",
                "description": "Find relationship path between two mathematical concepts",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "from_concept": {"type": "string", "description": "Starting concept ID"},
                        "to_concept": {"type": "string", "description": "Target concept ID"},
                        "max_depth": {"type": "integer", "description": "Maximum path length (default: 5)"}
                    },
                    "required": ["from_concept", "to_concept"]
                }
            },
            {
                "name": "prerequisites_for",
                "description": "Get prerequisite concepts needed to understand a concept (learning dependencies)",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "concept_id": {"type": "string", "description": "Concept to get prerequisites for"},
                        "depth": {"type": "integer", "description": "How deep to recurse (default: 3)"}
                    },
                    "required": ["concept_id"]
                }
            },
            {
                "name": "implementations_of",
                "description": "Find source files that implement a mathematical concept",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "concept_id": {"type": "string", "description": "Concept to find implementations for"}
                    },
                    "required": ["concept_id"]
                }
            },
            {
                "name": "search_concepts",
                "description": "Search mathematical concepts by keyword (searches names, aliases, definitions)",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "query": {"type": "string", "description": "Search term"}
                    },
                    "required": ["query"]
                }
            },
            {
                "name": "list_concepts",
                "description": "List all concepts in the knowledge graph, optionally filtered by category",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "category": {"type": "string", "description": "Optional: problem_class, algorithm, optimality, structure, or technique"}
                    }
                }
            },
            {
                "name": "solvers_for",
                "description": "Find algorithms that solve a specific problem class (e.g., 'LP', 'MIP', 'NLP')",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "problem_class": {"type": "string", "description": "Problem class to find solvers for"}
                    },
                    "required": ["problem_class"]
                }
            },
            {
                "name": "compare_algorithms",
                "description": "Compare two algorithms - what problems they solve, what they require, how they differ",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "algo1": {"type": "string", "description": "First algorithm to compare"},
                        "algo2": {"type": "string", "description": "Second algorithm to compare"}
                    },
                    "required": ["algo1", "algo2"]
                }
            },
            {
                "name": "get_algorithm_guidance",
                "description": "Get practical guidance for an algorithm - complexity, when to use, strengths/weaknesses",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "algorithm": {"type": "string", "description": "Algorithm name (e.g., 'simplex', 'interior_point', 'branch_and_bound')"}
                    },
                    "required": ["algorithm"]
                }
            },
            {
                "name": "suggest_approach",
                "description": "Get algorithm recommendations based on problem type and characteristics",
                "inputSchema": {
                    "type": "object",
                    "properties": {
                        "problem_type": {"type": "string", "description": "Problem type: LP, QP, NLP, MIP, MINLP"},
                        "characteristics": {
                            "type": "array",
                            "items": {"type": "string"},
                            "description": "Problem characteristics like: large, sparse, dense, reoptimization, convex, nonconvex, one-shot"
                        }
                    },
                    "required": ["problem_type"]
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

    # Knowledge Graph tools
    elif name == "explore_concept":
        result = kg.explore_concept(arguments.get("concept_id", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "find_path":
        result = kg.find_path(
            arguments.get("from_concept", ""),
            arguments.get("to_concept", ""),
            arguments.get("max_depth", 5)
        )
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "prerequisites_for":
        result = kg.prerequisites_for(
            arguments.get("concept_id", ""),
            arguments.get("depth", 3)
        )
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "implementations_of":
        result = kg.implementations_of(arguments.get("concept_id", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "search_concepts":
        results = kg.search_concepts(arguments.get("query", ""))
        return {"content": [{"type": "text", "text": json.dumps(results, indent=2)}]}

    elif name == "list_concepts":
        results = kg.list_concepts(arguments.get("category"))
        return {"content": [{"type": "text", "text": json.dumps(results, indent=2)}]}

    elif name == "solvers_for":
        result = kg.solvers_for(arguments.get("problem_class", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "compare_algorithms":
        result = kg.compare_algorithms(
            arguments.get("algo1", ""),
            arguments.get("algo2", "")
        )
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "get_algorithm_guidance":
        result = kg.get_algorithm_guidance(arguments.get("algorithm", ""))
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    elif name == "suggest_approach":
        result = kg.suggest_approach(
            arguments.get("problem_type", ""),
            arguments.get("characteristics", [])
        )
        return {"content": [{"type": "text", "text": json.dumps(result, indent=2)}]}

    return {"content": [{"type": "text", "text": f"Unknown tool: {name}"}], "isError": True}


def handle_resources_list() -> dict:
    """Return list of available resources."""
    return {
        "resources": [
            {
                "uri": "coinor://annotations",
                "name": "Full Annotations JSON",
                "description": "Complete source code annotations as JSON",
                "mimeType": "application/json"
            },
            {
                "uri": "coinor://knowledge-graph",
                "name": "Mathematical Concept Knowledge Graph",
                "description": "41 optimization concepts with relationships (requires, solves, implements)",
                "mimeType": "application/json"
            },
            {
                "uri": "coinor://concepts",
                "name": "Concept List",
                "description": "Quick reference list of all concepts by category",
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
    elif uri == "coinor://knowledge-graph":
        return {
            "contents": [
                {
                    "uri": uri,
                    "mimeType": "application/json",
                    "text": json.dumps(kg.data)
                }
            ]
        }
    elif uri == "coinor://concepts":
        # Return a compact concept list by category
        concepts_by_category = {}
        for cid, concept in kg.data.get('concepts', {}).items():
            cat = concept.get('category', 'unknown')
            if cat not in concepts_by_category:
                concepts_by_category[cat] = []
            concepts_by_category[cat].append({
                'id': cid,
                'name': concept.get('name', cid),
                'aliases': concept.get('aliases', []),
            })
        return {
            "contents": [
                {
                    "uri": uri,
                    "mimeType": "application/json",
                    "text": json.dumps(concepts_by_category, indent=2)
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
