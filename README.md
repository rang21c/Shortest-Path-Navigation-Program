# Shortest-Path-Navigation-Program

본 프로젝트에서는 그래프를 통한 최단 경로 탐색 프로그램을 구현한다. 이프로그램은 각 노드(상점)간의 경로를 찾게 된다. 이 프로그램은 도시에 대한 정보를 가지고 있는 로그 파일을 바탕으로 그래프를 생성하게 되며 구현된 그래프를 바탕으로 경로 탐색을 시행하게 된다. 상점의 거리 그래프 정보는 방향성과 가중치를 모두 가지고 있으며 Matrix 형태로 저장되어있다. 그래프를 생성한 이후 문자 비교를 통해 일부 그래프 가중치의 값을 변경하고 최소 비용 경로를 다익스트라,벨만포드,플로이드 알고리즘을 통해 탐색한다. 만약 Weight가 음수일 경우 다익스트라는 에러를 출력하며, 벨만-포드에서는 음수 사이클이 발생할 경우 에러 음수 사이클이 발생하지 않았을 경우 최단 경로와 거리를 구한다. 플로이드 에서는 음수 사이클이 발생한 경우 에러, 음수 사이클이 발생하지 않았을 경우 최단 경로와 거리를 구한다. 이후 다시 라빈 카프 알고리즘을 통해 문자열을 수정하게 된다.

### 1. 가게 정보 데이터
프로그램은 방향성과 가중치를 가지고 있는 그래프 정보를 형태로 섬의 거리 데이터를 저장한 Matrix텍스트 파일을 명령어를 통해 읽어 해당 정보를 클래스에 저장한다. 가게 데이터 텍스트 파일의 첫번째 줄에는 상점의 개수가 저장되어 있고 다음 줄 부터 섬의 거리 데이터가 저장되어 있다. 거리 데이터의 행과 열은 각각 Edge의 Start Vertex와 End Vertex의 Weight를 의미한다. 이중 첫번째 열은 ‘상점의 이름’ 이다.

![image](https://user-images.githubusercontent.com/33370179/174059013-fb8b1fde-4e40-402b-8f63-b3ab02776ed3.png)

Vertex와 Edge는 Linked-List를 이용하여 연결하며, 맵 데이터를 순차적으로 읽어 Linked-List 의 가장 끝에 연결한다(순차적으로 연결하여 반드시 Vertex 오름차순으로 정렬된 형태로 저장되어 있어야 한다). 만약 Linked-List의 값이 변경되어야 한다면 노드의 값을 수정하는게 아닌 새로운 노드를 생성하고 교체할 기존 노드를 삭제 해야 한다. (오름차 순으로 정렬된 상태이여야 함에 주의한다.)

![image](https://user-images.githubusercontent.com/33370179/174059063-b6304252-a414-421d-9187-7ad7bbe67643.png)

그래프의 최단경로 탐색 알고리즘을 탐색하기 전에 그래프의 가중치 정보는 가게의 이름에 따른 규칙에 의해 변경되어야 한다. 규칙은 아래와 같다. (3번 항목을 제외하고 비교항목에 공백문자가 있을경우 포함해서 비교하도록 한다.)

![image](https://user-images.githubusercontent.com/33370179/174059100-ffa127ef-d78b-40ca-8001-e8e8420f36c7.png)

### 2. 그래프 연산
프로그램은 텍스트 파일로부터 도로 정보 데이터를 읽은 뒤, 명령어에 따라 알맞은 그래프 연산을 수행할 수 있다.
- BFS

BFS 명령어는 Start Vertex와 End Vertex를 입력받아 경로와 거리를 구한다. 큐를 활용하여 구현한다. 
- DIJKSTRA

DIJKSTRA 명령어는 Start Vertex와 End Vertex를 입력받아 최단 경로와 거리를 구한다. Dijkstra 연산을 위해 STL set을 이용하여 최단 거리와 경로를 구하고, 결과로 찾은 최단경로를 다시 순회하여 Start Vertex부터 End Vertex 순으로 경로를 구한다.
- DIJKSTRAMIN

DIJKSTRAMIN 명령어는 DIJKSTRA 명령어와 동작이 동일하며, Dijkstra 연산을 위해 STL set을 활용 할 수 있다.
- BELLMANFORD

BELLMANFORD 명령어는 Start Vertex와 End Vertex를 입력받아 최단 경로와 거리를 구한다. Weight가 음수인 경우에도 정상 동작하며, 음수 Weight에 사이클이 발생한 경우에는 알맞은 에러를 출력한다.
- FLOYD

FLOYD 명령어는 입력 인자 없이 모든 쌍에 대해서 최단 경로 행렬을 구한다. Weight가 음수 인 경우에도 정상 동작하며, 음수 Weight에 사이클이 발생한 경우에는 알맞은 에러를 출력한다.

### 3. 정렬 연산
정렬 연산은 최단 경로로 방문한 노드를 정렬하여 출력한다 이번 프로젝트에서는 다양한 정렬 알고리즘의 사용을 통한 성능 비교를 진행한다.
성능의 측정은 Chrono 라이브러리를 통한 수행 시간을 통해 비교를 진행한다. (Chrono라이브러리의 사용이 힘들 경우 time으로 대체한다.)
![image](https://user-images.githubusercontent.com/33370179/174059385-59ba9b23-9ec7-4e9c-850d-0263986dcd8d.png)

구현하여 성능 비교를 진행해야 하는 정렬 알고리즘은 아래와 같다.
- Quick Sort
- Insert Sort
- Merge Sort
- Heap Sort
- Bubble Sort
각각의 정렬 알고리즘을 구현하여 보고 정렬 알고리즘을 바꾸었을 때 각각의 명령어 수행에 몇 초 간의 수행시간이 걸렸는지 도표로 정리하여 보고서에 추가한다.

### 4. 문자열 압축하기
최단 경로를 구하는 모든 알고리즘에 대하여 최단 경로를 찾고 난 후의 최종 출력물에 대하여 광장에 글자 새기기를 위한 다음과 같은 추가 작업을 진행한다.
만약 3에서의 출력이 아래와 같다면

![image](https://user-images.githubusercontent.com/33370179/174059524-2317df4f-ae82-4c5d-8fea-03a8afdd5bb1.png)

이는 0 1 3 가게 이름의 조합 즉 Denny's Bread Chodenny's Car shop Labuajiea's Yoga class으로 나타낼 수 있다. 이러한 문자열은 아래와 같은 법칙으로 압축될 수 있다.

![image](https://user-images.githubusercontent.com/33370179/174059660-fa2d5bcf-cbf2-41df-8090-8b4f474a6318.png)
