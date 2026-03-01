import time
import sys

""" Problem 2:
    
    This program serves as reference to help you develop your C program. 

    RUN: python or python3 2_algorithm input.fna average_TF.csv time.csv
    
    ** Please DO NOT run on the Schooner terminal (login node)! **
"""

# constants used in the C program
MAX_LINE_LENGTH = 1000000
GENE_ARRAY_SIZE = 164000
NUM_TETRANUCS   = 256
GENE_SIZE       = 10000



""" Store gene data here """
class Genes:
    gene_sequences = [''] * GENE_ARRAY_SIZE * GENE_SIZE  # gene sequences
    gene_sizes     = [0] * GENE_ARRAY_SIZE  # gene-sizes
    num_genes      = 0                      # total genes
""" --------------------------------- """



""" Read in the gene-data from a file """
def read_genes(inputFile):

    # return this
    genes = Genes()

    # remove the first header
    lines = inputFile.readlines()
    lines.pop(0)

    # read every line
    currentGeneIndex = 0
    for line in lines:

        # if the line is empty, quit
        if not line:
            break

        # if line is a DNA sequence, read it
        elif line[0] != '>':
            line_len = len(line)
            for i in range(line_len):
                c = line[i]
                if (c == 'A' or c == 'C' or c == 'G' or c == 'T'):
                    genes.gene_sequences[genes.num_genes * GENE_SIZE + currentGeneIndex] = c  # put letter into gene
                    currentGeneIndex += 1                                                     # increase currentGene size
                

        # if line is a header, reset
        else:
            genes.gene_sizes[genes.num_genes] = currentGeneIndex
            genes.num_genes += 1
            currentGeneIndex = 0

    # read in all genes, count the final one and return
    genes.gene_sizes[genes.num_genes] = currentGeneIndex
    genes.num_genes += 1
    return genes
""" --------------------------------- """



""" Process Tetranucs -------------------------- 
    Input: A DNA sequence of length N for a gene
    Output: The TF of this gene, which is an integer array of length 256

    For each i between 0 and N-4:
            Get the substring from i to i+3 in the DNA sequence
            This substring is a tetranucleotide
            Convert this tetranucleotide to its array index, idx
            TF[idx]++
"""
def process_tetranucs(genes, gene_TF, gene_index):

    # loop through the entire gene, computing a 4-letter substring at each step
    for i in range(genes.gene_sizes[gene_index] - 3):

        # for every 4 characters, get the character-value
        window = [0, 0, 0, 0]        
        substring = [
            genes.gene_sequences[gene_index * GENE_SIZE + (i + 0)],
            genes.gene_sequences[gene_index * GENE_SIZE + (i + 1)],
            genes.gene_sequences[gene_index * GENE_SIZE + (i + 2)],
            genes.gene_sequences[gene_index * GENE_SIZE + (i + 3)]
        ]

        # for every window-letter
        for c in range(4):

            # letter from the substring-window
            substring_i_c = substring[c]
            if substring_i_c == 'A':
                window[c] = 0
            elif substring_i_c == 'C':
                window[c] = 1
            elif substring_i_c == 'G':
                window[c] = 2
            elif substring_i_c == 'T':
                window[c] = 3

        # compute the index
        idx = window[0] * 64 + window[1] * 16 + window[2] * 4 + window[3]
        gene_TF[idx] += 1
""" --------------------------------- """



""" Algorithm
        Reference this algorithm for problem 2.
        For each gene in the list:
            Compute this gene’s TF
            Add this gene’s TF to the running total TF
            Compute the average TF from the running total TF
"""
def algorithm(inputFile, outputFile, timeFile):

    # access gene data with this
    genes = read_genes(inputFile)

    # count tetranucs here
    TF = [0] * NUM_TETRANUCS

    """ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ """
    # get start time
    start = time.time()

    # process tetranucs for each gene
    for gene_index in range(genes.num_genes):

        # compute this gene's TF
        gene_TF = [0] * NUM_TETRANUCS
        process_tetranucs(genes, gene_TF, gene_index)

        # add gene-TF to running total TF
        for t in range(NUM_TETRANUCS):
            TF[t] += gene_TF[t]

    # get the averages of each TF as a decimal
    average_TF = [0.0] * NUM_TETRANUCS
    for t in range(NUM_TETRANUCS):
        average_TF[t] = float(TF[t]) / float(genes.num_genes)

    # get end time
    end = time.time()
    """ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ """

    # print avg tetranucs
    for i in range(NUM_TETRANUCS):
        print(average_TF[i], file=outputFile)

    # print output time
    time_passed = end - start
    print(time_passed, file=timeFile)
""" --------------------------------- """



""" Main Program
        This is the main program.
"""
if __name__ == "__main__":
    # check for console errors
    argv = sys.argv
    if len(argv) != 4:
        print("USE LIKE THIS:\n2_algorithm.py input.fna average_TF.csv time.csv\n")
        exit(-1)

    # try to open files
    try:
        in_file   = open(argv[1], "r")
        out_file  = open(argv[2], "w")
        time_file = open(argv[3], "w")
    except Exception as err:
        print("ERROR: Cannot open files.")
        print(str(err))
        exit(-2)

    # run algorithm
    algorithm(in_file, out_file, time_file)
    in_file.close()
    out_file.close()
    time_file.close()
""" --------------------------------- """
