import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "poly_hub_burn"; // <= Name of the test
const testDirSuffix = "hub_burn"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xc3a1fabd7f8d290f7b0c45aa88af6e9c9e267843"; // <= Address of the smart contract
const chainID = 1;

// From : https://polygonscan.com/tx/0x6767ad075a7165e13334095de8ee5295f96d5777fc0cfd2af2b80e248ed5e064
const inputData =
  "0x42966c680000000000000000000000000000000000000000000000000000000000004efe";
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
    steps: 4, // <= Define the number of steps for this test case and this device
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
