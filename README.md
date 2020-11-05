# RNN_polymer_structure-property_w_Optimizations
	Polymeric Property Prediction
This repository contains recurrent neural networks for polymeric property prediction as described in the paper Dielectric Polymer Property Prediction Using Recurrent Neural Networks with Optimizations.
Both NormalizedBP and iRPROP- with optimization models are trained on a single tasking. 
Requirements
For small to medium datasets (~1000 to ~5000) in the SMILES decimal input representation it is possible to train models within minutes on a standard laptop using CPUs only. Same precautions for binary SMILES representation of larger sets will require a few hours.
	Data
For the purpose of training a model, one must provide two .dat files without any header rows: 1) chemical structures in the SMILES string format; 2) computationally or experimentally derived target values. Target values should be real numbers, unknown or invalid values should be discarded correspondingly. 
SMILES and target values (in the case of an example – dielectric constant), should be represented in a single column format.
//2.1.2_Max SMILES_length_calculation // Calculates the longest pattern in terms of the particular SMILES representation to be employed further as the number of hidden nodes for particular RNN model.
//2.3_Varification of the processing data// Verifies if the input file contains duplicates in the target data, otherwise assigns equal values.
	Data representation
SMILES input can be represented for further training and testing purposes in binary or decimal format. Once chosen to be represented in the binary format, the input is delivered as:
 
The decimal SMILES representation is reflected in the column format where each string type symbol is converted the corresponding one in the ASCII table.
Training/ Testing splits
Both codes support several activation functions and custom choice of the splitting data into training and testing pools. By default, the data is trained using 95% of the input samples, whereas testing is performed for the rest 5% of patterns. Alternatives can be specified in //1.3._Preparation of the test pool// section.
Section //3_Test pool data preparation// involves random setting of the weigh parameters of the input, output and context unit layers.
Custom features/ Hyperparameter Optimization
While the developed recurrent neural network architecture works quite well on a variety of datasets, optimization of certain hyperparameters forces noticeable improvement in prognosing performance. The optimization strategy for iRPROP- method includes greed search of parameter delta0 corresponding to the minimum of the loss function (denoted in the RMSE metrics). The optimization strategy for NormalyzedBP approach proceeds with finding optimal parameter ap responsible for reaching of global minimum in backpropagation approach. Parameter ap is denoted as Normalization_factor in session //1_Initialization of the working registers. Once hyperparameter optimization is complete, i.e. the corresponding loss function equals to the minimum value, the found optimal Normalization_factor (if Normalyzed_BP) and delta0 (if iRPROP-) should be applied for evaluation of prediction performance.

As an outline of the proposed RNN model, the table of concepts relative to both iRPROP- and Normalized_BP learning procedures is the following:
	
#### 1. Initialization of the working registers ####

#### 2. Data initialization ####

2.1 SMILES decoding (representation to binary format)

	2.1.1 Reading of the SMILES array

	2.1.2 Max SMILES length calculation

	 2.1.3 SMILES binary representation

	2.2 Array for eps values (targeted)

	 2.2.1 Decoding of the eps array (array of the targeted values)

	2.3 Verification of the processing data for the duplicates

3.	Test pool data preparation

3.1	SMILES decoding (representation to decimal)

4.	Learning procedure (iRPROP- or BP)

4.1	Weights initializations for the first, output and context unit layers

4.2	Learning itself (summator, activation functions)

4.2.1	(if present) Three step rule for iRPROP- learning algorithm

4.3	Learning using training set (epoch- or batch- dependent)

4.3.1	RMSE calculation for the testing and training pools

4.3.2	Resulted implementation of RNN
