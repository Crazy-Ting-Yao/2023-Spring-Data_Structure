#include <iostream>
#include <vector>
#include <string>
#include <functional>

struct Fruit {
    std::string      name;
    std::vector<int> hyperFeatures;
};

struct GradBinHyperWeight {
    int                featureIdx;
    double             gradSlider;
    int                binThreshold;
    GradBinHyperWeight *backwardContinuation = nullptr;
    GradBinHyperWeight *forwardContinuation = nullptr;
    
    bool shouldBackward(Fruit& f) const
    {
        return f.hyperFeatures[featureIdx] < binThreshold;
    }
    void applyGradSlider(Fruit& f) const
    {
        f.hyperFeatures[featureIdx] = (int) ((double) f.hyperFeatures[featureIdx] * gradSlider);
    }
};
int o;

void recursion(std::vector<Fruit>& fruits, GradBinHyperWeight* gbhw){
    std::vector<Fruit> left, right;
    for(auto& f : fruits){
        gbhw->applyGradSlider(f);
        if(gbhw->shouldBackward(f)) left.push_back(f);
        else right.push_back(f);
    }
    if(left.size()){
        if(gbhw->backwardContinuation == nullptr) std::cout << left[0].name << " " << left[0].hyperFeatures[gbhw->featureIdx] << std::endl;
        else recursion(left, gbhw->backwardContinuation);
    }
    if(right.size()){
        if(gbhw->forwardContinuation == nullptr) std::cout << right[0].name << " " << right[0].hyperFeatures[gbhw->featureIdx] << std::endl;
        else recursion(right, gbhw->forwardContinuation);
    }
}


int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<Fruit> fruits(n);
    for (int i = 0; i < n; i++) {
        std::cin >> fruits[i].name;
        fruits[i].hyperFeatures.resize(m);
        for (int j = 0; j < m; j++) {
            std::cin >> fruits[i].hyperFeatures[j];
        }
    }
    std::cin >> o;
    std::vector<GradBinHyperWeight> GBHW(o+1);
    for(int i = 1; i <= o; i++) std::cin >> GBHW[i].featureIdx >> GBHW[i].gradSlider >> GBHW[i].binThreshold;
    for(int i = 1; i <= o; i++){
        if(i*2<=o) GBHW[i].backwardContinuation = &GBHW[i*2];
        else GBHW[i].backwardContinuation = nullptr;
        if(i*2+1<=o) GBHW[i].forwardContinuation = &GBHW[i*2+1];
        else GBHW[i].forwardContinuation = nullptr;
    }
    recursion(fruits, &GBHW[1]);
}