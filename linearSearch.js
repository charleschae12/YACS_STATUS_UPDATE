function linearSearch(arr, target) {
  for (let i in arr) {
    if (arr[i] === target) return i
  }
  return -1
}
console.log(linearSearch([1, 2, 3, 4], 1)) // 0
console.log(linearSearch([1, 2, 3, 4], 4)) // 3
console.log(linearSearch([1, 2, 3, 4], 6)) // -1
console.log(linearSearch([3, 4, 1, 6, 3], 6)) // 3