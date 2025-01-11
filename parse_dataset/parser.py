import argparse
import json
from collections import Counter


def parse_config(config_file):
    """Parse the configuration file and return a dictionary mapping symbols to descriptions."""
    config = {}
    with open(config_file, 'r') as f:
        for line in f:
            if "=" in line:
                symbol, description = line.strip().split("=", 1)
                config[symbol.strip()] = description.strip()
    return config


def parse_data(data_file):
    """Parse the data file and return the sequence as a string."""
    with open(data_file, 'r') as f:
        return f.read().strip()


def calculate_probabilities(data, config):
    """Calculate probabilities for each position, ignoring unknown symbols."""
    counts = Counter(data)  # Count occurrences of all characters in data
    valid_symbols = set(config.keys())  # Get the valid symbols from the config
    
    # Keep only valid symbols in the counts dictionary
    filtered_counts = {k: v for k, v in counts.items() if k in valid_symbols}
    total = sum(filtered_counts.values())  # Sum of valid counts

    if total == 0:
        raise ValueError("No valid data points found after filtering. Check your data and configuration files.")
    
    # Calculate probabilities
    probabilities = {k: (filtered_counts[k] / total) * 100 for k in valid_symbols}
    return probabilities, total


def write_readable_output(probabilities, num_data_points, config):
    """Write a human-readable output file."""
    with open("readable_output.txt", 'w') as f:
        f.write(f"There were {len(config)} positions possible, each position with these probabilities based on {num_data_points} data points:\n")
        for symbol, description in config.items():
            prob = probabilities.get(symbol, 0)
            f.write(f"{symbol} ({description}) = {prob:.2f}%\n")


def write_delimited_output(probabilities, config):
    """Write the output to a text file with | delimiter."""
    with open("probabilities.txt", 'w') as f:
        # Write the header
        # f.write("symbol|description|probability\n") # Comment in to write header
        
        # Write each symbol's data
        for symbol, description in config.items():
            prob = probabilities.get(symbol, 0)
            f.write(f"{symbol}|{description}|{prob:.2f}\n")


def main():
    parser = argparse.ArgumentParser(
        description="Parse pig position data based on a given configuration.\n"
                    "The data file should be formatted as:\n"
                    "\tjbbjjbbjjbjbjbjj\n"
                    "The config file should be formatted as:\n"
                    "\tj = leaning jowler\n"
                    "\tb = black dot side",
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("-d", "--data", required=True, help="Path to the data file.")
    parser.add_argument("-c", "--config", required=True, help="Path to the configuration file.")

    args = parser.parse_args()

    # Parse files
    config = parse_config(args.config)
    data = parse_data(args.data)

    # Calculate probabilities
    probabilities, num_data_points = calculate_probabilities(data, config)

    # Write outputs
    write_readable_output(probabilities, num_data_points, config)
    write_delimited_output(probabilities, config)


if __name__ == "__main__":
    main()
