import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "mumbai_hub_mint"; // <= Name of the test
const testDirSuffix = "hub_mint"; // <= directory to compare device snapshots to
const testNetwork = "mumbai";
const signedPlugin = false;

const contractAddr = "0xc3a1fabd7f8d290f7b0c45aa88af6e9c9e267843"; // <= Address of the smart contract
const chainID = 1;

const inputData =
  "0xf08e8f5e00000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f000000000000000000000000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000057465737465000000000000000000000000000000000000000000000000000000";
// Create serializedTx and remove the "0x" prefix
const value = "3.1";
const serializedTx = populateTransaction(
  contractAddr,
  inputData,
  chainID,
  value
);
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
];

devices.forEach((device) =>
  processTest(
    device,
    contractName,
    testLabel,
    testDirSuffix,
    "",
    signedPlugin,
    serializedTx,
    testNetwork
  )
);
