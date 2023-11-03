import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "mumbai_hub_change_del_exec_with_sign"; // <= Name of the test
const testDirSuffix = "hub_change_del_exec_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "mumbai";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/tx/0x2db76baa9e4d5863a9642dd0ef5c04e34ebd9d3e5187205406ddb1f658c3b331
const inputData =
  "0x4926c4ed00000000000000000000000000000000000000000000000000000000000000770000000000000000000000000000000000000000000000000000000000000140000000000000000000000000000000000000000000000000000000000000018000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000d9ecbdf322a934f99d85268d506c079997ea54e7000000000000000000000000000000000000000000000000000000000000001b26b6e147713c1cd0b56bf7ac367c2791ec9094d9c248511aeb988bb25f8e92a917dbcec5366ee235ca9808bd0bd84d3a4ecb5119da3bd2f2c67c7b8695e773c00000000000000000000000000000000000000000000000000000000065140d4400000000000000000000000000000000000000000000000000000000000000010000000000000000000000006c1e1bc39b13f9e0af9424d76de899203f47755f00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000001";
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
    steps: 12, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 8, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 8, // <= Define the number of steps for this test case and this device
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
