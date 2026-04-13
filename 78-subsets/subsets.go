func subsets(nums []int) [][]int {
    result := [][]int{{}}

    for _, num := range nums {
        size := len(result)
        for i := 0; i < size; i++ {
            // 今ある集合(result)のこぴーを作成し、新しい要素を追加する
            // Goのスライスは参照型なので、明示的に新しいスライスを作成する必要がある
            nextSubset := make([]int, len(result[i]))
            copy(nextSubset, result[i])
            nextSubset = append(nextSubset, num)

            //　結果に追加
            result = append(result, nextSubset)
        }
    }
    return result
}