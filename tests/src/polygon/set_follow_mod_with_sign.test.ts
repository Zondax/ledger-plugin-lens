import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_set_follow_mod_with_sign"; // <= Name of the test
const testDirSuffix = "set_follow_mod_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d#writeProxyContract
const inputData =
  "0xce30bb4f00000000000000000000000000000000000000000000000000000000000000040000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000095f98009962a0164f7be1114ed9469c91337e89e000000000000000000000000000000000000000000000000000000000000001be7c04443e2ba33152bb59e69cba7abf629900761fd83da5f6ab5e20039844f355c8e6cf942dcd268ae9398ebf97ed743b3a15df1dac17745129fdcee2d40337a00000000000000000000000000000000000000000000000000000000650d882c0000000000000000000000000000000000000000000000000000000000000000";
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
    steps: 9, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 6, // <= Define the number of steps for this test case and this device
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
