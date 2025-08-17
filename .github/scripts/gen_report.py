#!/usr/bin/env python3
import argparse
import json
from collections import defaultdict
from common.util import utils
from common.util.utils import FunctionStatus
from report_pb2 import Report, Measures

def compute_measures(version: str | None = None) -> Measures:
    counts = defaultdict(int)
    sizes = defaultdict(int)

    total_code = 0
    total_functions = 0

    for func in utils.get_functions(version=version):
        counts[func.status] += 1
        sizes[func.status] += func.size
        total_code += func.size
        total_functions += 1

    matched_code = sizes[FunctionStatus.Matching]
    matched_functions = counts[FunctionStatus.Matching]

    fuzzy_code = matched_code + sizes[FunctionStatus.NonMatching] + sizes[FunctionStatus.Equivalent]

    m = Measures()
    m.total_code = total_code
    m.matched_code = matched_code
    m.matched_code_percent = (matched_code / total_code * 100) if total_code else 0.0
    m.fuzzy_match_percent = (fuzzy_code / total_code * 100) if total_code else 0.0

    m.total_functions = total_functions
    m.matched_functions = matched_functions
    m.matched_functions_percent = (matched_functions / total_functions * 100) if total_functions else 0.0

    m.total_data = 0
    m.matched_data = 0
    m.matched_data_percent = 0.0
    m.complete_data = 0
    m.complete_data_percent = 0.0

    m.total_units = 0
    m.complete_units = 0


    return m

def build_report(version: str | None = None) -> Report:
    report = Report()
    report.version = 1
    report.measures.CopyFrom(compute_measures(version))
    return report

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version", help="CSV version to read")
    parser.add_argument("--output", "-o", help="Output JSON file")
    args = parser.parse_args()

    report = build_report(args.version)

    from google.protobuf.json_format import MessageToJson
    json_str = MessageToJson(report, indent=2)

    if args.output:
        with open(args.output, "w") as f:
            f.write(json_str)
    else:
        print(json_str)

if __name__ == "__main__":
    main()
