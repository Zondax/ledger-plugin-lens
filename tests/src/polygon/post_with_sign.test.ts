import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_post_with_sign"; // <= Name of the test
const testDirSuffix = "hub_post_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d#writeProxyContract
const inputData =
  "0x907cd7d200000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000acab2c2cdde3a5839b91babeffd5fd5128590d6f000000000000000000000000000000000000000000000000000000000000001bd4cb809743f6d9499d90136889cb879432bf9109e33b971bce4521ae7fddb00666e947d821c898a27abe962ce73e66b521aef7c897e937f172e55ac833b2ecf900000000000000000000000000000000000000000000000000000000651434c7000000000000000000000000000000000000000000000000000000000000001d00000000000000000000000000000000000000000000000000000000000000c000000000000000000000000000000000000000000000000000000000000001200000000000000000000000000000000000000000000000000000000000000160000000000000000000000000acab2c2cdde3a5839b91babeffd5fd5128590d6f00000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000000000035697066733a2f2f516d54566a3951674a3970534e424d375843624341695266574b576a38636b436832505743597245785637673356000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000005fe7918c3ef48e6c5fd79dd22a3120a3c4967ac200000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000014000000000000000000000000098dad8b389417a5a7d971d7f83406ac7c646a8e2000000000000000000000000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000e000000000000000000000000000000000000000000000000000038d7ea4c6800000000000000000000000000000000000000000000000000000000000000000640000000000000000000000009c3c9283d3e44854697cd22d3faa240cfb03288900000000000000000000000000000000000000000000000000000000000007d000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000acab2c2cdde3a5839b91babeffd5fd5128590d6f0000000000000000000000000000000000000000000000000000000000000000";
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
    steps: 8, // <= Define the number of steps for this test case and this device
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
