import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_burn"; // <= Name of the test
const testDirSuffix = "hub_burn"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xe7e7ead361f3aacd73a61a9bd6c10ca17f38e945"; // <= Address of the smart contract
const chainID = 1;

//https://polygonscan.com/address/0xe7E7EaD361f3AaCD73A61A9bD6C10cA17F38E945#writeProxyContract
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
