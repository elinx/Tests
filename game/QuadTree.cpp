#include <iostream>

#include <list>
#include <vector>
#include <memory>

using std::list;
using std::vector;
using std::shared_ptr;

class Rectangle{
public:
    enum class SUBSPACE{
        UR,
        UL,
        DL,
        DR
    };
private:
    int                             m_x;
    int                             m_y;
    int                             m_width;
    int                             m_height;

public:
    Rectangle()
        : m_x(0)
        , m_y(0)
        , m_width(0)
        , m_height(0){

        }
    Rectangle(int x, int y, int width, int height)
        : m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height){

        }

    bool intersect(const Rectangle& rhs){

    }
    /**
     * Get the one sub-rectangle of this rectangle
     */
    shared_ptr<Rectangle> subRectangle(SUBSPACE part){
        switch(part){
            case SUBSPACE::UR: return shared_ptr<Rectangle>(new Rectangle(m_x + m_width << 1, m_y, m_width << 1, m_height << 1));
            case SUBSPACE::UL: return shared_ptr<Rectangle>(new Rectangle(m_x, m_y, m_width << 1, m_height << 1));
            case SUBSPACE::DL: return shared_ptr<Rectangle>(new Rectangle(m_x, m_y + m_height << 1, m_width << 1, m_height << 1));
            case SUBSPACE::DR: return shared_ptr<Rectangle>(new Rectangle(m_x + m_width << 1, m_y + m_height << 1, m_width << 1, m_height << 1));
        }
        return nullptr;
    }
    /**
     * Determine whether the rhs rectangle can be fitted
     * into this rectangle
     */
    bool fitIn(const Rectangle& rhs){
        if(    rhs.m_x >= m_x 
            && rhs.m_y >= m_y
            && rhs.m_x + rhs.m_width <= m_x + m_width 
            && rhs.m_y + rhs.m_height <= m_y + m_height)
            return true;
        return false;
    }
    /**
     * Determine whether the rhs rectangle can be fitted
     * into the any sub-rectangle of this rectangle.
     */
    bool fitIn(const Rectangle& rhs, SUBSPACE part){
        return subRectangle(part)->fitIn(rhs);
    }
};

template<
    typename T,
    typename Rectangle
>
class Entity{
private:
    T*                  m_object;
    Rectangle           m_bound;

public:
    Entity()
        : m_object(nullptr)
        , m_bound(new Rectangle()){

        }

    Rectangle* getBound(){
        return m_bound;
    }
};


template<
	typename Entity,
	typename Rectangle
>
class QuadTree{

private:
    static const int    MAXNODES = 4;               // QuadTree has 4 nodes
    static const int    MAXENTITY = 10;             // One node has at most 10 objects

private:
    vector< shared_ptr<QuadTree> >  m_nodes;
    list< shared_ptr<Entity> >      m_entity;
    Rectangle*                      m_bound;
    int                             m_level;

public:
    QuadTree(int level, Rectangle* rect)
    	: m_nodes(MAXNODES, new QuadTree())
    	, m_entity(0, nullptr)
    	, m_bound(rect)
        , m_level(level) {
    }

    void addEntity(Entity* entity){
        addEntity(this, entity);
    }
    /**
     * Determine whether the entity of the root node is full, if false
     * find the right sub-rectangle which the entity can fully fit into
     * and add it into the entity list or add it into the node it self;
     * if true split the root node into four parts and add the entity of
     * the root into the subnodes seperatly and clear the entitys of the
     * root node.
     */
    void addEntity(QuadTree* root, Entity* entity){
        if(MAXENTITY > root->m_entity.size()){
            int index = root->getIndex(entity->getBound());

            if(-1 != index){
                root->m_nodes.at(index)->addEntity(root->m_nodes.at(index), entity);
            } else {
                // non-leaf node cannot hold data.
                // root->m_entity->push_back(entity);
            }
        }else{
            root->m_entity.add(entity);
            root->split();

            for(auto ent : root->m_entity){
                int index = root->getIndex(ent);
                if(-1 != index){
                    root->m_nodes.at(index)->addEntity(root->m_nodes.at(index), ent);
                }
            }
            root->clearEntity();
        }
    }

private:
    /**
     * Split the current node into 4 subnodes, push the subnodes in
     * anti-clockwise order and the level of subnodes is current level
     * plus one.
     */
    void split(){
        m_nodes.push_back(new QuadTree(m_level + 1, m_bound->subRectangle(Rectangle::SUBSPACE::UR)));        // RU
        m_nodes.push_back(new QuadTree(m_level + 1, m_bound->subRectangle(Rectangle::SUBSPACE::UL)));        // LU
        m_nodes.push_back(new QuadTree(m_level + 1, m_bound->subRectangle(Rectangle::SUBSPACE::DL)));        // LD
        m_nodes.push_back(new QuadTree(m_level + 1, m_bound->subRectangle(Rectangle::SUBSPACE::DR)));        // RD
    }
    /**
     * Determine which node the object belongs to.
     * -1 means the object cannot completely fit within a child node and
     * is part of the parent node
     */
    int getIndex(Rectangle* bound){
        if(bound->fitIn(m_bound, Rectangle::RU)) return 0;
        else if(bound->fitIn(m_bound, Rectangle::LU)) return 1;
        else if(bound->fitIn(m_bound, Rectangle::RD)) return 2;
        else if(bound->fitIn(m_bound, Rectangle::LD)) return 3;

        return -1;
    }
    /**
     * Clear all entitys of the node
     */
    void clearEntity(){
        if (!m_entity.empty())
        {
            for(auto iter : m_entity){
                iter->release();
            }
        }
    }

};//End of QuadTree declaretion


int main()
{
   
   return 0;
}
