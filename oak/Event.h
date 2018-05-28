#pragma once

//////////////////////////////////////////////////////////////////////////
template< typename ListenerType>
class Event
    {
    public:
        void operator += (ListenerType * pListener)
            {
            m_aListeners.push_back(pListener);
            }

        void operator -= (ListenerType * pListener)
            {
            auto revIter = m_aListeners.rbegin();
            for (; revIter != m_aListeners.rend(); ++revIter)
                if (revIter == pListener)
                    {
                    m_aListeners.remove(revIter);
                    break;
                    }
            }

        template<typename CallFunction>
        void Signal(CallFunction c) {
            for (auto l : m_aListeners)
                c(l);
            }

    private:
        std::vector<ListenerType *> m_aListeners;

    };

